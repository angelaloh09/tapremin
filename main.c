#include <MKL25Z4.h>
#include "touch_sensor.h"
#include "buzzer.h"
#include "matrix.h"

int freq_high(int x);
int freq_low(int x);
int touch;
int freq;

/*
 * [main] integrates the touch sensor, piezo buzzer, and led matrix components
 * all together.
 */
int main(void) {
	touch_init(); //initializing touch sensor
	buzzer_init(); //initializing buzzer
	SPI0_init(); //initializing SPI
	MAX7219_init(); //initializing LED matrix

	while(1) {
		touch = touch_scan_LH(); //get finger placement on touch sensor
		if (touch > 140) { //flag to detect if the touch sensor senses anything
			freq = freq_low(touch); //map touch sensor value to a frequency
			buzzer_play(freq); //buzzer outputs sound at that frequency
			led_show_low(freq); //led matrix shows led pattern wrt that frequency
		} else { //nothing touching touch sensor
			buzzer_stop(); //stops the buzzer
			led_stop(); //stops the led matrix
		}
	}
    return 0;
}

//[freq_low] maps the touch sensor location [int x] to a low range frequency
int freq_low(int x){
	if (x <= 313){
		return 262; // C4
	} else if (x <= 493){
		return 294; // D4
	} else if (x <= 673){
		return 330; // E4
	} else if (x <= 853){
		return 349; // F4
	} else {
		return 392; // G4
	}
}

//[freq_high] maps the touch sensor location [int x] to a high range frequency
int freq_high(int x){
	if (x <= 320){
		return 523; // C5
	} else if (x <= 540){
		return 587; // D5
	} else if (x <= 760){
		return 659; // E5
	} else if (x <= 980){
		return 698; // F5
	} else {
		return 784; // G5
	}
}