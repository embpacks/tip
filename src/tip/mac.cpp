/*
 * mac.hpp
 *
 *  Created on: 4 juni 2018
 *      Author: SERAGUD
 */

#include "tip/mac.hpp"

void Mac::receivePacket(const uint8_t *buf, uint32_t size) {
	for(Layer3handler& handler: handlers) {
		if(handler.receivePacket(buf, size)) {
			break;
		}
	}
}

void sendPacket(const uint8_t *buf, uint32_t size) {

}
