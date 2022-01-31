#ifndef BUZZER_H_
#define BUZZER_H_

/*
 * [buzzer_init] initializes the piezo buzzer and pit timer for PWM.
 */
void buzzer_init(void);

/*
 * [buzzer_play] takes in [int freq] and the piezo buzzer will output a
 * sound wave corresponding to that frequency value.
 */
void buzzer_play(int freq);

/*
 * [buzzer_stop] stops the piezo buzzer from outputting anything
 */
void buzzer_stop(void);

/*
 *  [PIT_IRQHandler] is the interrupt handler for the PIT timer.
*/
void PIT_IRQHandler(void);

#endif /* BUZZER_H_ */