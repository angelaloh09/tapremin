# tapremin
Immersive music experience -- just for fun

Tapremin is designed to be an immersive musical experience, inspired by the theremin. Players use the touch slider on the FRDM-KL25Z board to control the frequency of the sound output by the piezo buzzers, and can see a visual representation of the musical notes on a LED matrix that is connected in the system.*

To create the immersive experience, the project links up two FRDM-KL25Z microcontrollers, two piezo buzzers, and one LED matrix. Two microcontrollers are designed for the system, and each microcontroller is linked up to its own piezo buzzer. A user will slide or tap his/her finger across both touch sensors from the two microcontrollers, and the position that the user places their finger on the touch sensor is mapped to a specific sound frequency value. The piezo buzzers will play the sounds to allow the user to register what note he/she is playing, and the LED matrix will light up also with respect to the sound frequency. The greater the frequency, the more rows of LEDs are lit up on the matrix. *Note that the LED matrix must be powered separately.
