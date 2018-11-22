/*
 * netif.cpp
 *
 *  Created on: 4 juni 2018
 *      Author: SERAGUD
 */

#include "utils.h"
#include "tip/tip.hpp"

bool Ip4::isIncomingAddrBroadcast(Ip4Addr& addr) const {
	if (addr == Ip4Addr::broadcast)
		return true;
	if (addr == Ip4Addr::any)
		return true;

	// TODO can i handle broadcast?

	if (addr == address)
		return false;

	return addr.isBroadcastOn(address, netmask);
}

bool Ip4::canHandleIncomingAddr(Ip4Addr& addr) const {
	if (!isUp())
		return false;
	if (address.isAny())
		return false;

	// Unicast to my address?
	if (address == addr)
		return true;

	if (isIncomingAddrBroadcast(addr))
		return true;

	if (addr.isLoopback())
		return true;

	// TODO autoip

	return false;
}

void Ip4::receivePacket(uint8_t * const buf, uint32_t const bufLen) {
	if (bufLen < Ip4HeaderLen) {
		return;
	}

	Ip4Header &header = *(Ip4Header *) buf;

	if (header.getVersion() != 4) {
		return;
	}

	uint16_t const headerLen = header.getHeaderLength() * 4;
	uint16_t const totalLen = header.getLength();

	if (totalLen < bufLen) {
		// TODO wrong package?
		return;
	}

	if (headerLen < Ip4HeaderLen) {
		return;
	}

	Ip4Addr dstAddr = header.getDestAddr();

	// TODO verify checksum

	if (dstAddr.isMulticast()) {
		// TODO
	} else {
		if (canHandleIncomingAddr(dstAddr)) {
			handlePacket(buf, bufLen);
			return;
		}
		// TODO probe other interfaces
		return;
	}

	// TODO accept DHCP packet

	return;
}

void Ip4::handlePacket(uint8_t * const buf, uint32_t const bufLen) {
	// TODO Validate src ip

	Ip4Header &header = *(Ip4Header *) buf;

	Ip4RxPacket* packet;

	Ip4FragBuf* tfrag;
	if (header.getOffset() != 0 || header.getMoreFragFlag()) {
		tfrag = findFragment(header);
		if (tfrag == NULL) {
			tfrag = findFreeFragment();
		}
		if (tfrag == NULL) {
			// Drop packet
			return;
		}
		Ip4FragBuf& frag = *tfrag;
		frag.copyFragment(header, &buf[Ip4HeaderLen]);
		if (!frag.hasCompleted()) {
			return;
		}
		auto temp = Ip4RxPacket(frag.header, frag.buf, frag.packetLen);
		packet = &temp;
	} else {
		auto temp = Ip4RxPacket(*(Ip4Header *) buf, &buf[Ip4HeaderLen],
				header.getLength() - Ip4HeaderLen);
		packet = &temp;
	}

	switch (header.protocol) {
	case Ip4Protocol_Tcp:
		tcpHandler.handlePacket(*packet);
		break;
	case Ip4Protocol_Udp:
		udpHandler.handlePacket(*packet);
		break;
	case Ip4Protocol_Icmp:
		icmpHandler.handlePacket(*packet);
		break;
	default:
		break;
	}

	// Free the fragment buffer
	if (tfrag != NULL) {
		utils_clear_mem(tfrag, sizeof(Ip4FragBuf));
	}
}

void Ip4::sendPacket(uint8_t * data, uint16_t length) {
	if (length > IpMaxDataSize) {
		// TODO
		return;
	}

	// TODO
}

