/*
 * chroma.c
 *
 *  Created on: Feb 1, 2022
 *      Author: ble
 */


/*
 * mfcc.c
 *
 *  Created on: Oct 21, 2021
 *      Author: Brandon
 */

#include "chroma.h"
#include "const.h"
#include "arm_math.h"
#include "plot.h"
#include <stdlib.h>
#include <math.h>
extern float mag_print;

static void window(float real_vals[], float windowed_vals[]) {
	for (int i = 0; i < FFT_SIZE; i++) {
		windowed_vals[i] = (0.54 - 0.46*cos(2*3.14159*i/(FFT_SIZE - 1))) * real_vals[i];
	}
}

static void convert_to_complex(float real_vals[], float32_t complex_vals[]) {
	for (int i = 0; i < FFT_SIZE; i++) {
		complex_vals[2 * i] = (float32_t) real_vals[i];
		complex_vals[2 * i + 1] = 0;
	}
}

static void get_magnitude(float32_t complex_vals[], float mag_vals[]) {
	for(int i = 0; i < FFT_SIZE; i++) {
		float real = complex_vals[2 * i];
		float imag = complex_vals[2 * i + 1];
		float mag = sqrt((real * real) + (imag * imag));
		mag_vals[i] = mag;
	}
}

static void get_psd(float32_t complex_vals[], float periodogram[]) {
	arm_cfft_instance_f32 fft_handler;
	arm_cfft_init_f32(&fft_handler, FFT_SIZE);
	arm_cfft_f32(&fft_handler, complex_vals, 0, 1);

	float mag_array[FFT_SIZE] = {0};
	get_magnitude(complex_vals, mag_array);
	for (int i = 0; i < FFT_SIZE; i++) {
		mag_array[i] = (mag_array[i] * mag_array[i]);
	}

	float periodogram_energy = 0;
	for (int i = 0; i < FFT_SIZE / 2; i++) {
		periodogram[i] = mag_array[i];
		periodogram_energy += mag_array[i];
	}
	for (int i = 0; i < FFT_SIZE / 2; i++) {
		periodogram[i] /= periodogram_energy;
	}
	//plot(periodogram, FFT_SIZE / 2, 0);
	//int largest_k = get_peak(periodogram, FFT_SIZE / 2);
	//HAL_Delay(5);
}

static void chroma_analysis(float periodogram[], float chroma[], float octaves[]) {
	for (int k = 1; k < FFT_SIZE/2; k++) {
		/*
		float first_log = log(FS * ((float) k) / (FFT_SIZE * 440));
		float final_log = first_log/log(2);
		float first_conversion = 12 * final_log;
		float round_value = 69 + first_conversion;
		*/
		int midi = round(69 + (12 * (log(FS * (float) k / (FFT_SIZE * 440)) / log(2))));
		if (midi < 0) {
			continue;
		}
		int chroma_ind = midi % 12;
		int octave = midi / 12;
		chroma[chroma_ind] += periodogram[k];
		octaves[octave] += periodogram[k];
	}
}

void get_chroma(float real_vals[], float chroma[], float octaves[]) {
	float windowed_vals[FFT_SIZE] = {0};
	window(real_vals, windowed_vals);
	float32_t complex_vals[2 * FFT_SIZE] = {0};
	convert_to_complex(windowed_vals, complex_vals);
	float periodogram[FFT_SIZE/2] = {0};
	get_psd(complex_vals, periodogram);
	chroma_analysis(periodogram, chroma, octaves);
}

void normalize_chroma(float chroma[], float octaves[], float normalized_chroma[], float normalized_octaves[]) {
	float chroma_energy = 0;
	float octave_energy = 0;
	for (int i = 0; i < CHROMA_SIZE; i++) {
		chroma_energy += chroma[i];
	}
	for (int i = 0; i < CHROMA_SIZE; i++) {
		normalized_chroma[i] = chroma[i] / chroma_energy;
	}
	for (int i = 0; i < OCTAVE_SIZE; i++) {
		octave_energy += octaves[i];
	}
	for (int i = 0; i < OCTAVE_SIZE; i++) {
		normalized_octaves[i] = octaves[i] / octave_energy;
	}
}

