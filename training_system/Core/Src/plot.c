/*
 * plot.c
 *
 *  Created on: Feb 5, 2022
 *      Author: ble
 */

#include "plot.h"
#include "const.h"
#include "arm_math.h"
#include <stdlib.h>
#include <math.h>
extern float mag_print;


void plot(float buff[], int size, int complex) {
	if (complex == 0) {
		for(int i = 0; i < size; i++) {
			mag_print = buff[i];
			HAL_Delay(10);
		}
	}
	else {
		for(int i = 0; i < size; i++) {
			mag_print = buff[2 * i];
			HAL_Delay(10);
		}
	}
}

int get_peak(float in_buff[], int size) {
	float peak_val = -1;
	int index = -1;
	for(int i = 0; i < size; i++) {
		if (in_buff[i] > peak_val) {
			peak_val = in_buff[i];
			index = i;
		}
	}
	return index;
}


