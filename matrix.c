#include "MKL25Z4.h"
#include "matrix.h"

void SPI0_init(void);
void SPI0_write(unsigned char data);
void max7219_write(unsigned char command, unsigned char data);

#define DECODE 9
#define INTENSITY 10
#define SCANLIMIT 11
#define SHUTDOWN 12
#define TEST 15

/*
 * [MAX7219_init] initializes the LED Matrix
 */
void MAX7219_init(void){
	max7219_write(DECODE, 0xFF); 	/* decode B mode */
	max7219_write(SCANLIMIT, 0x7); 	/* scan eight digits */
	max7219_write(INTENSITY, 0); 	/* set lowest intensity */
	max7219_write(TEST, 0); 		/* disable test mode */
	max7219_write(SHUTDOWN, 1); 	/* enable device */
}

/*
 * [SPI0_init] initializes the SPI communication protocol
 */
void SPI0_init(void) {
	SIM->SCGC5 |= 0x1000; 			/* enable clock to Port D */
	PORTD->PCR[1] = 0x200; 			/* make PTD1 pin as SPI SCK */
	PORTD->PCR[2] = 0x200; 			/* make PTD2 pin as SPI MOSI */
	PORTD->PCR[0] = 0x100; 			/* make PTD0 pin as GPIO */
	PTD->PDDR |= 0x01; 				/* make PTD0 as output pin for CS */
	PTD->PSOR = 0x01; 				/* make CS default high */
	SIM->SCGC4 |= 0x400000; 		/* enable clock to SPI0 */
	SPI0->C1 = 0x10; 				/* disable SPI and make SPI0 master */
	SPI0->BR = 0x60; 				/* set Baud rate to 1 MHz */
	SPI0->C1 |= 0x40; 				/* Enable SPI module */
}

/*
 * [max7219_write] takes in [unsigned char command] and
 * an [unsigned char data] value in order to index into the LED matrix
 * and turn on the LED pixels corresponding to the command and data value
 */
void max7219_write(unsigned char command, unsigned char data) {
	volatile char dummy;
	PTD->PCOR = 1; 					/* set CS low */
	while(!(SPI0->S & 0x20)) { } 	/* wait until tx ready */
	SPI0->D = command; 				/* send command byte first */
	while(!(SPI0->S & 0x80)) { } 	/* wait until tx complete */
	dummy = SPI0->D; 				/* clear SPRF */
	while(!(SPI0->S & 0x20)) { } 	/* wait until tx ready */
	SPI0->D = data; 				/* send data byte */
	while(!(SPI0->S & 0x80)) { } 	/* wait until tx complete */
	dummy = SPI0->D; 				/* clear SPRF */
	PTD->PSOR = 1; 					/* set CS high */
}

/*
 * [led_show_high] takes in a high [int freq] and outputs an LED pattern
 * pattern that corresponds to the frequency on the matrix.
 */
void led_show_high(int freq){
	switch(freq){
		case 523: //C5
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0x0F); //LED row 3 off
			max7219_write(0x04, 0x0F); //LED row 4 off
			max7219_write(0x05, 0x0F); //LED row 5 off
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 587: //D5
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0x0F); //LED row 4 off
			max7219_write(0x05, 0x0F); //LED row 5 off
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 659: //E5
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0xF8); //LED row 4 on
			max7219_write(0x05, 0x0F); //LED row 5 off
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 698: //F5
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0xF8); //LED row 4 on
			max7219_write(0x05, 0xF8); //LED row 5 on
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 784: //G5
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0xF8); //LED row 4 on
			max7219_write(0x05, 0xF8); //LED row 5 on
			max7219_write(0x06, 0xF8); //LED row 6 on
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
	}
}

/*
 * [led_show_low] takes in a low [int freq] and outputs an LED pattern
 * pattern that corresponds to the frequency on the matrix.
 */
void led_show_low(int freq){
	switch(freq){
		case 262: //C4
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0x0F); //LED row 3 off
			max7219_write(0x04, 0x0F); //LED row 4 off
			max7219_write(0x05, 0x0F); //LED row 5 off
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 294: //D4
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0x0F); //LED row 4 off
			max7219_write(0x05, 0x0F); //LED row 5 off
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 330: //E4
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0xF8); //LED row 4 on
			max7219_write(0x05, 0x0F); //LED row 5 off
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 349: //F4
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0xF8); //LED row 4 on
			max7219_write(0x05, 0xF8); //LED row 5 on
			max7219_write(0x06, 0x0F); //LED row 6 off
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
		case 392: //G4
			max7219_write(0x01, 0x0F); //LED row 1 off
			max7219_write(0x02, 0xF8); //LED row 2 on
			max7219_write(0x03, 0xF8); //LED row 3 on
			max7219_write(0x04, 0xF8); //LED row 4 on
			max7219_write(0x05, 0xF8); //LED row 5 on
			max7219_write(0x06, 0xF8); //LED row 6 on
			max7219_write(0x07, 0x0F); //LED row 7 off
			max7219_write(0x08, 0x0F); //LED row 8 off
			break;
	}
}

/*
 * [led_stop] clears all patterns on the LED matrix and outputs nothing.
 */
void led_stop(void){
	max7219_write(0x01, 0x0F); //LED row 1 off
	max7219_write(0x02, 0x0F); //LED row 2 off
	max7219_write(0x03, 0x0F); //LED row 3 off
	max7219_write(0x04, 0x0F); //LED row 4 off
	max7219_write(0x05, 0x0F); //LED row 5 off
	max7219_write(0x06, 0x0F); //LED row 6 off
	max7219_write(0x07, 0x0F); //LED row 7 off
	max7219_write(0x08, 0x0F); //LED row 8 off
}