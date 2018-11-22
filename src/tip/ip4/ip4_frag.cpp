/*
 * tip.cpp
 *
 *  Created on: 24 apr. 2018
 *      Author: SERAGUD
 */

#include "utils.h"

#include <stdint.h>
#include <tip/tip.hpp>

enum {
	Ip4NumBuf = 5,
	Ip4SupportedTotalSize = 5000,
	Ip4NumFragMems = 10,
	Ip4FragMemsPerBuf = 10,
};

static Ip4FragBuf fragBufs[Ip4NumBuf];

void* Ip4FragMem::operator new(size_t size) {
	// TODO lock
	for (int i = 0; i < Ip4NumFragMems; i++) {
		if (fragMems[i].isUsed)
			continue;
		fragMems[i].isUsed = true;
		// TODO unlock
		return &fragMems[i];
	}
	// TODO unlock
	return nullptr;
}

Ip4FragBuf* findFragment(Ip4Header &header) {
	for (int i = 0; i < Ip4NumBuf; i++) {
		if (fragBufs[i].doesBelongsTo(header)) {
			return &fragBufs[i];
		}
	}
	return NULL;
}

Ip4FragBuf* findFreeFragment() {
	for (int i = 0; i < Ip4NumBuf; i++) {
		if (fragBufs[i].isFree()) {
			return &fragBufs[i];
		}
	}
	return NULL;
}
