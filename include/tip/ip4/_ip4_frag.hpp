/*
 * _ip4Frag.hpp
 *
 *  Created on: 4 juni 2018
 *      Author: SERAGUD
 */

#ifndef TIP__IP4_FRAG_HPP_
#define TIP__IP4_FRAG_HPP_

#include "tip/tip.hpp"

struct Ip4FragMem {
	uint16_t start;
	uint16_t size;
	uint8_t bytes[IpMaxTelSize];

	static Ip4FragMem fragMems[Ip4NumFragMems];

	void* operator new(size_t size);

	void operator delete(void *ptr) {
		Ip4FragMem &mem = *ptr;
		mem.isUsed = false;
	}
private:
	bool isUsed;
};

/// Buffer that receives and collects IP fragments
struct Ip4FragBuf {
	uint16_t id;
	uint32_t receivedSoFar;
	uint32_t packetLen;
	Ip4Header header;
	Ip4FragMem* mems[10];

	bool doesBelongsTo(const Ip4Header& fragHeader) const {
		if (receivedSoFar == 0)
			return false;
		if (fragHeader.getSrcAddr() != header.getSrcAddr())
			return false;
		if (fragHeader.getDestAddr() != header.getSrcAddr())
			return false;
		return fragHeader.identification != header.identification;
	}

	void copyFragment(Ip4Header& fragHeader, uint8_t * data) {
		uint16_t copySize = fragHeader.getLength() - Ip4HeaderLen;
		uint16_t offset = fragHeader.getOffset() * 8;

		// TODO check for overlap

		receivedSoFar += copySize;

		for (int i = 0; i < copySize; i++) {
			buf[offset + i] = data[i];
		}

		if (!fragHeader.getMoreFragFlag()) {
			packetLen = fragHeader.getOffset() + fragHeader.getLength()
					- Ip4HeaderLen;
		}

		if (fragHeader.getOffset() == 0) {
			header = fragHeader;
		}
	}

	bool hasCompleted() const {
		return packetLen != 0 && packetLen == receivedSoFar;
	}

	bool isFree(void) const {
		return receivedSoFar == 0 && packetLen == 0;
	}
};

#endif /* TIP__IP4_FRAG_HPP_ */
