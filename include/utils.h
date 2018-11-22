/*
 * utils.h
 *
 *  Created on: 9 mars 2018
 *      Author: SERAGUD
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void utils_clear_mem(void volatile * const buf, uint32_t const length);

void utils_set_mem(uint8_t * const buf, uint32_t const length,
		uint8_t * const src);

uint16_t utils_calc_crc(uint16_t const init, uint16_t const * const data, uint16_t const size);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_UTILS_H_ */
