# tapremin
## created by angela loh & jenny wen

An Immersive music experience 

Introduction
Tapremin is designed to be an immersive musical experience, inspired by the theremin. Players use the touch slider on the FRDM-KL25Z board to control the frequency of the sound output by the piezo buzzers, and can see a visual representation of the musical notes on a LED matrix that is connected in the system. Best of all, it's portable! Batteries power the board so you can bring the party with you anywhere.*

To create the immersive experience, our project links up two FRDM-KL25Z microcontrollers, two piezo buzzers, and one LED matrix. We designated two microcontrollers to our system, and each microcontroller is linked up to its own piezo buzzer. A user will slide or tap his/her finger across both touch sensors from the two microcontrollers, and the position that the user places their finger on the touch sensor is mapped to a specific sound frequency value. The piezo buzzers will play the sounds to allow the user to register what note he/she is playing, and the LED matrix will light up also with respect to the sound frequency. The greater the frequency, the more rows of LEDs are lit up on the matrix.

From this project, the biggest milestone that we accomplished is learning how to interface the FRDM-KL25Z board with external hardware. Most of this semester, we have been strictly working with hardware that is embedded inside the microcontroller’s breakout board, such as the built-in LED. However, by adding additional hardware to our system, such as the LED matrix and piezo buzzers, we were challenged to initialize communication protocols that we previously haven’t worked with, understand how the data transmission or data latching works on a register level, and implement code to configure the touch sensor.

*Note that the LED matrix must be powered separately.

System Overview
Below is the infrastructure diagram that models how the different hardware parts in the system interface with each other, as well as the software infrastructure diagram that lays out the different helper functions and files in our code.

hardware infrastructure software infrastructure
