#ifndef __TOUCH_SEN_H_
#define __TOUCH_SEN_H_

#include <MKL25Z4.h>

/*
 * [touch_init] is the TSI initialization function
 */
void touch_init(void);


/*
 * [touch_scan_LH] reads touch sensor from low to high capacitance for left to right
 */
int touch_scan_LH(void);

/*
 * [touch_scan_HL] reads touch sensor from high to low capacitance for left to right
 */
int touch_scan_HL(void);

#define SCAN_OFFSET 544  // Offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // Accessing the bits held in TSI0_DATA_TSICNT

#endif