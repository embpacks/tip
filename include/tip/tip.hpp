/*
 * tip.h
 *
 *  Created on: 24 apr. 2018
 *      Author: SERAGUD
 */

#ifndef TIP_TIP_HPP_
#define TIP_TIP_HPP_

#include <tip/ip4/ip4.hpp>
#include "types.h"
#include <iostream>


using namespace std;

enum {
	/// Ip4 maximum telegram size
	IpMaxTelSize = 1500,
	/// Ip4 header size without options
	Ip4HeaderLen = 20,
	/// Ip4 maximum payload size
	IpMaxDataSize = IpMaxTelSize - Ip4HeaderLen,
};

typedef enum {
	Ip4Protocol_Icmp = 1,
	Ip4Protocol_Igmp = 2,
	Ip4Protocol_Udp = 17,
	Ip4Protocol_UdpLite = 136,
	Ip4Protocol_Tcp = 6,
} Ip4Protocol;

struct Ip4Addr;

struct __attribute__((packed)) Ip4Header {
private:
	uint8_t version_ihl;

	union {
		uint8_t dscp;
		uint8_t ecn;
	};

	uint16_t totalLength;

public:
	uint16_t identification;

private:
	uint16_t flags_fragOffset;

	uint8_t ttl;

public:
	uint8_t protocol;

private:
	uint16_t checksum;

	uint32_t srcAddr;

	uint32_t destAddr;

public:
	uint8_t getVersion(void) const {
		return version_ihl >> 4;
	}

	void setVersion(uint8_t const version) {
		version_ihl &= 0x0f;
		version_ihl |= version << 4;
	}

	uint8_t getHeaderLength(void) const {
		return version_ihl & 0xf;
	}

	void setHeaderLength(uint8_t const hl) {
		version_ihl &= 0xf0;
		version_ihl |= hl & 0xf;
	}

	uint16_t getLength(void) const {
		return uint16_switchEndian(totalLength);
	}

	void setLength(uint16_t const length) {
		totalLength = uint16_switchEndian(length);
	}

	Ip4Addr getSrcAddr() const;

	// TODO set Src address

	Ip4Addr getDestAddr() const;

	// TODO set Dest address

	uint16_t getOffset(void) const {
		return (uint16_switchEndian(flags_fragOffset) & 0x1fff);
	}

	void setOffset(uint16_t const offset) {
		flags_fragOffset &= 0x00e0;
		flags_fragOffset |= uint16_switchEndian(offset & 0x1fff);
	}

	bool getReservedFlag(void) const {
		return (flags_fragOffset & 0x0080) != 0;
	}

	void setReservedFlag(bool const flag) {
		flags_fragOffset &= 0x0080;
		if (flag)
			flags_fragOffset |= 0x0080;
	}

	bool getDontFragFlag(void) const {
		return (flags_fragOffset & 0x0040) != 0;
	}

	void setDontFragFlag(bool const flag) {
		flags_fragOffset &= 0x0040;
		if (flag)
			flags_fragOffset |= 0x0040;
	}

	bool getMoreFragFlag(void) const {
		return (flags_fragOffset & 0x0020) != 0;
	}

	void setMoreFragFlag(bool const flag) {
		flags_fragOffset &= 0x0020;
		if (flag)
			flags_fragOffset |= 0x0020;
	}
};

struct __attribute__((packed)) Ip4Addr {
public:
	union {
		uint32_t addr;
		uint8_t bytes[4];
	};

	Ip4Addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

	Ip4Addr(uint32_t addr, bool bigendian = false);

	Ip4Addr network(const Ip4Addr& netmask) const;

	Ip4Addr host(Ip4Addr netmask) const {
		return Ip4Addr(addr & ~netmask.addr, true);
	}

	bool isMulticast(void) const {
		return (bytes[0] & 0xf0) == 0xe0;
	}

	bool isLinkLocal(void) const {
		return (bytes[0] == 0xa9) && (bytes[1] == 0xfe);
	}

	bool isLoopback(void) const {
		return addr == loopback.addr;
	}

	bool isAny(void) const {
		return addr == any.addr;
	}

	bool isBroadcast(void) const {
		return addr == broadcast.addr;
	}

	bool isBroadcastOn(const Ip4Addr& ip, const Ip4Addr& netmask) const {
		if (ip.network(netmask) != this->network(netmask))
			return false;

		return host(netmask) == broadcast.host(netmask);
	}

	bool operator==(const Ip4Addr& other) const {
		return addr == other.addr;
	}

	bool operator==(const Ip4Addr&& other) const {
		return addr == other.addr;
	}

	bool operator!=(Ip4Addr& other) const {
		return !(addr == other.addr);
	}

	bool operator!=(Ip4Addr&& other) const {
		return !(addr == other.addr);
	}

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

#endif /* TIP_TIP_HPP_ */
