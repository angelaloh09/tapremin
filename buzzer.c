#include <MKL25Z4.h>
#include "buzzer.h"

volatile int count = 0; // counter for units of time elapsed


/*
 * [buzzer_init] initializes the piezo buzzer and pit timer for PWM.
 */
void buzzer_init(){
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //Enable the clock to port E
	PORTE->PCR[20] = PORT_PCR_MUX(001); //Set up PTE20 as GPIO
	PTE->PDDR |= (1 << 20);		    //Enable PTE20 as an output

	NVIC_EnableIRQ(PIT_IRQn); // enable NVIC for PIT

	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;   // Enable clock to PIT module
	PIT->MCR = PIT_MCR_MDIS(0); 	    // turn on PIT
	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE(1); // enable the interrupt to cause an interrupt event
}

/*
 * [buzzer_play] takes in [int freq] and the piezo buzzer will output a
 * sound wave corresponding to that frequency value.
 */
void buzzer_play(int freq){
	NVIC_EnableIRQ(PIT_IRQn);
	PIT->CHANNEL[0].LDVAL = (int) 10485760 / freq;	// set load value of zeroth PIT - clock speed 10.48576 MHz
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN(1); 	// enable the timer so it starts to count down
}

/*
 * [buzzer_stop] stops the piezo buzzer from outputting anything
 */
void buzzer_stop(){
	NVIC_DisableIRQ(PIT_IRQn);
}

/*
 * [PIT_IRQHandler] is the interrupt handler for the PIT timer.
 */
void PIT_IRQHandler(void)
{
	count = count + 1;
	if(count == 1) {
		PTE->PCOR |= (1 << 20);    // 0 for 1 unit of time
	} else {
		PTE->PSOR |= (1 << 20);    // 1 for 1 unit of time
		count = 0;
	}

	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK; // writing 1 to this flag clears it
}