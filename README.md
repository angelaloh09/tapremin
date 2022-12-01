# Tapremin
by angela loh & jenny wen

### An Immersive music experience 

#### Introduction
Tapremin is designed to be an immersive musical experience, inspired by the theremin. Players use the touch slider on the FRDM-KL25Z board to control the frequency of the sound output by the piezo buzzers, and can see a visual representation of the musical notes on a LED matrix that is connected in the system. Best of all, it's portable! Batteries power the board so you can bring the party with you anywhere.*

To create the immersive experience, our project links up two FRDM-KL25Z microcontrollers, two piezo buzzers, and one LED matrix. We designated two microcontrollers to our system, and each microcontroller is linked up to its own piezo buzzer. A user will slide or tap his/her finger across both touch sensors from the two microcontrollers, and the position that the user places their finger on the touch sensor is mapped to a specific sound frequency value. The piezo buzzers will play the sounds to allow the user to register what note he/she is playing, and the LED matrix will light up also with respect to the sound frequency. The greater the frequency, the more rows of LEDs are lit up on the matrix.

From this project, the biggest milestone that we accomplished is learning how to interface the FRDM-KL25Z board with external hardware. Most of this semester, we have been strictly working with hardware that is embedded inside the microcontroller’s breakout board, such as the built-in LED. However, by adding additional hardware to our system, such as the LED matrix and piezo buzzers, we were challenged to initialize communication protocols that we previously haven’t worked with, understand how the data transmission or data latching works on a register level, and implement code to configure the touch sensor.

#### System Overview
Below is the infrastructure diagram that models how the different hardware parts in the system interface with each other, as well as the software infrastructure diagram that lays out the different helper functions and files in our code.
<img width="500" alt="hw_infrastructure" src="https://user-images.githubusercontent.com/44074422/205133528-3df0847d-ca88-411d-9c51-6af73e748fa1.png">
<img width="500" alt="sw_infrastructure" src="https://user-images.githubusercontent.com/44074422/205133584-b360809b-0aca-45b2-a892-e6b8a15330d3.png">

#### Detailed Technical Description 
##### Schematic: 
<img align="left" alt="schematic" src="https://user-images.githubusercontent.com/44074422/205133842-5ce15c83-90e2-4681-9219-a1e9745304b5.png" width = 500>

The touch sensor is built into the board, so it does not have any external pin connections. The buzzer connects to PTE20 (a GPIO pin) and GND. The LED matrix is powered through the 5V line from the FRDM-KL25Z board and connected to GND. For the SPI communication between the LED matrix and the board, we are using SPI0 for the clock and MOSI signals, and PTD0 (a GPIO pin) as the chip select pin.

MCU2 is connected in a similar way, except without the LED matrix.

##### Touch Sensing Input (TSI)
First, the clock is enabled on the TSI port through the System Clock Gating Control Register 5 (SCGC5). The touch sensor is then initialized with the correct settings for our application through the General Control and Status Register. Of note, we set the TSI to be in capacitive sensing mode, so that it could give us continuous values along the slider. We also enabled the TSI through the TSIEN bit, and cleared the End of Scan Flag (EOSF).

We used the DATA register to read the values from the slider. We wanted the slider to give higher values on the right side in the way that we were orienting the board, so we set up channel 10 to do so. To start a scan, we set the Software Trigger Start (SWTS) bit. We then read the scanned data stored in the TSICNT bits before clearing the EOSF.

##### Piezo Buzzer
The buzzer requires a PWM signal with a 50% duty cycle and desired frequency (this was verified through testing). We decided to use the Periodic Interrupt Timer (PIT) to do this. For initialization, we first enabled the clock to port E through SCGC5, and set up PTE20 as an output. We then enabled interrupt requests from the PIT through the Nested Vector Interrupt Controller (NVIC), enabled the clock to the PIT through SCGC6, turned the PIT on through the PIT Module Control Register (MCR), and enabled interrupts through the Timer Control Register (TCTRL).

To play sound through the buzzers, we made sure that interrupt requests were enabled, set the proper load value by dividing the PIT clock speed (10.48576 MHz) by our desired note frequency, and enabled the timer so it starts to count down. The PIT IRQ handler toggled PTE20 once the time had elapsed, and cleared the interrupt flag as well.

We also wanted the buzzer to be able to stop playing sound (i.e. when the touch sensor does not sense anything), and the way we did this was by disabling interrupt requests from the PIT.

##### LED Matrix
The LED matrix uses SPI communication protocol to receive data from the microcontroller. We decided to use the SPI0 channel. To initialize the protocol, we first enabled the clock on Port D by writing to the System Clock Gating Control Register 5 (SGCG5). Then, we defined the SPI clock line (SCK), SPI Master Out Slave In line (MOSI), and Chip Select line (CS) by loading in MUX values that correspond to the pinout selection that we need for SPI. These values were all written to the different channels of the Port D Control Register (PCR). After the different pinouts were established, we enabled the clock specifically for SPI0 by writing SGCG4, making SPI0 the master, setting the baud rate for data transmission to 1MHz, and lastly, enabling the SPI module. After initializing SPI, we initialized the LED matrix. We did so by defining the DECODE mode to be decode B mode, SCANLIMIT range to be able to scan 8 digits, and the INTENSITY of the LEDs to be the lowest intensity.

To get the LED matrix to show an LED pattern that corresponded to a specific frequency, we first set the Chip Select line to low. Then, we wrote a while loop to wait for the transmission line to be ready. Once it is ready, a command is written to the Data register for SPI0 defining which row of the LED matrix we want to select. Then, after the transmission has completed, we clear the SPI Receiver Full register (SPRF), and load in the value of the how many LED segments we want to show (since the MAX7219 chip is configured for a 7-segment display). After that transmission is complete, we clear the SPRF again and set the Chip Select line back to high. We then created a mapping function that would check the frequency of which we want the output to represent and the LED pattern that corresponds that the frequency. In each of these mappings, we index to specific rows of the matrix and set specific LEDs to either turn on or turn off.

#### Testing Scheme
##### Touch Sensor
To test the touch slider on the FRDM boards, we used the debugger in MCUXpresso and set watch expressions to see the values with our fingers at different positions on the slider. We recorded the maximum and minimum values we could reproducibly get, and calibrated which ranges of values would correspond to each frequency this way as well.

##### Piezo Buzzer
To test the piezo buzzer, we first generated a square wave using a function generator in order to verify functionality. We noticed that the buzzer worked with a 50% duty cycle square wave with the frequency of the desired sound output.

<img align="center" src="https://user-images.githubusercontent.com/44074422/205134176-808302a6-40bd-4ffb-b020-cc3493de2c1d.png" width="500" height="300" />

We then initialized the first channel on the PIT with some hard coded load values corresponding to specific frequency values to see whether a PWM signal generated from our boards this way worked. Finally, we integrated the touch sensor with the buzzer and listened to the sound output by the buzzers. We realized that the sound from the buzzers was cleaner when something was obstructing the opening at the top, so we put tape on top of it for the final demo.

##### LED Matrix
For the LED Matrix, we created a write function that took in two parameters: a command parameter and a data parameter. In the command parameter, we tested different values after reading the datasheet for the matrix, and discovered that we could index into the rows of the LED matrix. For the data parameter, we also read the datasheet and tested different hex values that we could write to the data register of the matrix. Initially, some really weird patterns showed up on the matrix that we were not able to decipher towards the start. However, after several iterations of testing different command and data parameter values we discovered a pattern to how to control the LED.

LED Matrix Bug: 
<img src="https://user-images.githubusercontent.com/44074422/205134176-808302a6-40bd-4ffb-b020-cc3493de2c1d.png](https://user-images.githubusercontent.com/44074422/205135038-b8a5c604-4db2-4d3f-9847-cc52ab85e61c.jpg)" width="500" height="300" />

LED Matrix Working: 
<img src="https://user-images.githubusercontent.com/44074422/205134952-04f09504-0e5f-49f8-859e-cae6526745fd.jpg" width="500" height="300" />

Testing if our function was working properly was pretty straight forward for the matrix. Since we had the hardware component, our testing procedure involved writing to the LED matrix and observing if the pattern we wanted to appear on the matrix was the correct one that was showing up.

##### Additional Resources Used
- KL25 Sub-Family Reference Manual
- [TSI example]([url](https://forum.digikey.com/t/using-the-capacitive-touch-sensor-on-the-frdm-kl46z/13246))
- MAX7219 [datasheet]([url](https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf))
- MAX7219 SPI example
