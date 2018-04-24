/*
 * tip.h
 *
 *  Created on: 24 apr. 2018
 *      Author: SERAGUD
 */

#ifndef TIP_TIP_H_
#define TIP_TIP_H_

#include "types.h"
#include <iostream>

using namespace std;

typedef enum {
	Ip4Protocol_Icmp = 1,
	Ip4Protocol_Igmp = 2,
	Ip4Protocol_Udp = 17,
	Ip4Protocol_UdpLite = 136,
	Ip4Protocol_Tcp = 6,
} Ip4Protocol;

class __attribute__((packed)) Ip4Header {
	union {
		uint8_t version;
		uint8_t ihl;
	};

	union {
		uint8_t dscp;
		uint8_t ecn;
	};

	uint16_t totalLength;

	uint16_t identification;

	union {
		uint16_t flags;
		uint16_t fragOffset;
	};

	uint8_t ttl;

	uint8_t protocol;

	uint16_t checksum;

	uint32_t srcAddr;

	uint32_t destAddr;

	void init() {

	}
};

class Ip4Addr;

class __attribute__((packed)) Ip4Addr {
public:
	union {
		uint32_t addr;
		uint8_t bytes[4];
	};

	Ip4Addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

	Ip4Addr(uint32_t addr, bool bigendian = false);

	Ip4Addr network(uint32_t netmask);

	Ip4Addr network(uint32_t netmask[4]);

	Ip4Addr network(Ip4Addr netmask);

	/// 255.255.255.255
	static const Ip4Addr none;

	/// 127.0.0.1
	static const Ip4Addr loopback;

	/// 0.0.0.0
	static const Ip4Addr any;

	/// 255.255.255.255
	static const Ip4Addr broadcast;
};

ostream& operator<<(ostream& os, Ip4Addr& addr);

static_assert(sizeof(Ip4Addr) == 4, "Ip4Addr shall be of size 4");

#endif /* TIP_TIP_H_ */
