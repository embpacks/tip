/*
 * tip.cpp
 *
 *  Created on: 24 apr. 2018
 *      Author: SERAGUD
 */

#include "tip/tip.h"

#include <stdint.h>

const Ip4Addr Ip4Addr::none = Ip4Addr(0xffffffffUL);

const Ip4Addr Ip4Addr::loopback = Ip4Addr(0x7f000001UL);

const Ip4Addr Ip4Addr::any = Ip4Addr(0x00000000UL);

const Ip4Addr Ip4Addr::broadcast = Ip4Addr(0xffffffffUL);

Ip4Addr::Ip4Addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	bytes[0] = a;
	bytes[1] = b;
	bytes[2] = c;
	bytes[3] = d;
}

Ip4Addr::Ip4Addr(uint32_t addr, bool bigendian) {
	if (!bigendian) {
		bytes[0] = uint32_get_byte3(addr);
		bytes[1] = uint32_get_byte2(addr);
		bytes[2] = uint32_get_byte1(addr);
		bytes[3] = uint32_get_byte0(addr);
	} else {
		this->addr = addr;
	}
}

Ip4Addr Ip4Addr::network(uint32_t netmask) {
	return Ip4Addr(addr & netmask);
}

Ip4Addr Ip4Addr::network(uint32_t netmask[4]) {
	return Ip4Addr(bytes[0] & netmask[0], bytes[1] & netmask[1],
			bytes[2] & netmask[2], bytes[3] & netmask[3]);
}

Ip4Addr Ip4Addr::network(Ip4Addr netmask) {
	return Ip4Addr(addr & netmask.addr, true);
}

ostream& operator<<(ostream& os, Ip4Addr& addr) {
	os << uint32_t(addr.bytes[0]) << '.' << uint32_t(addr.bytes[1]) << '.'
			<< uint32_t(addr.bytes[2]) << '.' << uint32_t(addr.bytes[3]);
	return os;
}

void ip4Receive(uint8_t *buf, uint32_t length) {


	// TODO
}
