#ifndef MATRIX_H_
#define MATRIX_H_

/*
 * [SPI0_init] initializes the SPI communication protocol
 */
void SPI0_init(void);


/*
 * [MAX7219_init] initializes the LED Matrix
 */
void MAX7219_init(void);


/*
 * [max7219_write] takes in [unsigned char command] and
 * an [unsigned char data] value in order to index into the LED matrix
 * and turn on the LED pixels corresponding to the command and data value
 */
void max7219_write(unsigned char command, unsigned char data);


/*
 * [led_show_high] takes in a high [int freq] and outputs an LED pattern
 * pattern that corresponds to the frequency on the matrix.
 */
void led_show_high(int freq);


/*
 * [led_show_low] takes in a low [int freq] and outputs an LED pattern
 * pattern that corresponds to the frequency on the matrix.
 */
void led_show_low(int freq);


/*
 * [led_stop] clears all patterns on the LED matrix and outputs nothing.
 */
void led_stop(void);

#endif /* MATRIX_H_ */