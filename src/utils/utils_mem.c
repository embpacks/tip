/*
 * utils_mem.c
 *
 *  Created on: 9 mars 2018
 *      Author: SERAGUD
 */

#include "utils.h"

void utils_clear_mem(void volatile * const buf, uint32_t const length) {
	for (uint32_t i = 0; i < length; i++) {
		((uint8_t *)buf)[i] = 0;
	}
}

void utils_set_mem(uint8_t * const buf, uint32_t const length,
		uint8_t * const src) {
	for (uint32_t i = 0; i < length; i++) {
		buf[i] = src[i];
	}
}

uint16_t utils_calc_crc(uint16_t const init, uint16_t const * const data, uint16_t const size) {
	// TODO
	return 0;
}
