/*
 * netif.hpp
 *
 *  Created on: 4 juni 2018
 *      Author: SERAGUD
 */

#ifndef TIP_NETIF_HPP_
#define TIP_NETIF_HPP_

#include "tip/tip.hpp"

class Ip4RxPacket {
public:
	Ip4Header& header;
	uint8_t* buf;
	uint16_t length;

	Ip4RxPacket(Ip4Header& header, uint8_t* buf, uint16_t length) :
			header(header), buf(buf), length(length) {
	}

	Ip4RxPacket(Ip4RxPacket& other) :
			header(other.header), buf(other.buf), length(other.length) {
	}

	Ip4RxPacket(Ip4RxPacket&& other) :
			header(other.header), buf(other.buf), length(other.length) {
	}
};

struct Layer4Handler {
public:
	virtual void handlePacket(Ip4RxPacket& packet) = 0;
};

class Ip4 {
public:
	// IP address configuration

	Ip4Addr address;

	Ip4Addr netmask;

	Ip4Addr gateway;

	char* hostname;

	Layer4Handler &tcpHandler;

	Layer4Handler &udpHandler;

	Layer4Handler &icmpHandler;

	bool isIncomingAddrBroadcast(Ip4Addr& addr) const;

	bool canHandleIncomingAddr(Ip4Addr& addr) const;

	void receivePacket(uint8_t * const buf, uint32_t const bufLen);

	void sendPacket(uint8_t * data, uint16_t length);

	bool isUp(void) const {
		return true;
	}

private:
	void handlePacket(uint8_t * const buf, uint32_t const bufLen);
};

#endif /* TIP_NETIF_HPP_ */
