/*
 * fft.c
 *
 *  Created on: Oct 9, 2021
 *      Author: ble
 */


//#include <fft.h>
/*
int mag_print;

void preprocess(uint16_t in_buff[const], float32_t out_buff[], int size) {
	float32_t sine_average = 0;
	for(int i = 0; i < size; i++) {
		sine_average += (float) in_buff[i];
	}
	sine_average /= size;
	for(int i = 0; i < size; i++) {
		out_buff[2 * i] = in_buff[i] - sine_average;
		out_buff[2 * i + 1] = 0;
	}

	//if (size < 1024 && size != 256) {
		//for (int i = size; i < 1024; i++) {
			//out_buff[2 * i] = 0;
			//out_buff[2 * i + 1] = 0;
		//}
	//}

}



void plot(float32_t buff[], int size, uint8_t complex) {
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

void get_magnitude(float32_t in_buff[], float32_t out_buff[], int size) {
	for(int i = 0; i < size; i++) {
		float32_t real = in_buff[2 * i];
		float32_t imag = in_buff[2 * i + 1];
		out_buff[i] = sqrt((real * real) + (imag * imag));
	}
}

void get_two_peaks(float32_t in_buff[], int size, int indexes[]) {
	float32_t peak_val = -1;
	int first_index = -1;
	int second_index = -1;
	for(int i = 0; i < size/2; i++) {
		if (in_buff[i] > peak_val) {
			peak_val = in_buff[i];
			first_index = i;
		}
	}
	peak_val = -1;
	for(int i = size/2; i < size; i++) {
		if (in_buff[i] > peak_val) {
			peak_val = in_buff[i];
			second_index = i;
		}
	}
	indexes[0] = first_index;
	indexes[1] = second_index;
}
*/
