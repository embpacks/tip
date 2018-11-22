/*
 * mac.hpp
 *
 *  Created on: 4 juni 2018
 *      Author: SERAGUD
 */

#ifndef TIP_MAC_HPP_
#define TIP_MAC_HPP_

#include <vector>

using namespace std;

struct Layer3handler {
	bool receivePacket(const uint8_t * buf, uint32_t const bufLen);

	void sendPacket(uint8_t * data, uint16_t length);
};

struct MacAddr {
	uint8_t macAddr[6];

	MacAddr(uint8_t* macAddr) {
		for (int i = 0; i < 6; i++) {
			this->MacAddr[i] = macAddr[i];
		}
	}
};

/// MAC layer
struct Mac {
	/// MAC address
	MacAddr macAddr;

	vector<Layer3handler*> handlers;

	Mac(MacAddr addr) :
			macAddr(macAddr) {
	}

	void receivePacket(const uint8_t *buf, uint32_t size);

	void sendPacket(const uint8_t *buf, uint32_t size);
};

#endif /* TIP_MAC_HPP_ */
