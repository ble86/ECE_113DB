/*
 * chroma.h
 *
 *  Created on: Feb 1, 2022
 *      Author: ble
 */

#ifndef INC_CHROMA_H_
#define INC_CHROMA_H_

void get_chroma(float periodogram[], float chroma[], float octaves[]);
void normalize_chroma(float chroma[], float octaves[], float normalized_chroma[], float normalized_octaves[]);

#endif /* INC_CHROMA_H_ */
