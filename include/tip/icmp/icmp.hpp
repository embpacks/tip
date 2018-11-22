/*
 * icmp.h
 *
 *  Created on: 24 apr. 2018
 *      Author: SERAGUD
 */

#ifndef TIP_ICMP_HPP_
#define TIP_ICMP_HPP_

typedef enum {
	/// Echo reply
	Icmp_ER = 0,
	/// Destination unreachable
	Icmp_DUR = 3,
	/// Source quench
	Icmp_SQ = 4,
	/// Redirect
	Icmp_RD = 5,
	/// Echo
	Icmp_ECHO = 8,
	/// Time exceeded
	Icmp_TE = 11,
	/// Parameter problem
	Icmp_PP = 12,
	/// Timestamp
	Icmp_TS = 13,
	/// Timestamp reply
	Icmp_TSR = 14,
	/// Information request
	Icmp_IRQ = 15,
	/// Information reply
	Icmp_IR = 16,
	/// Address mask request
	Icmp_AM = 17,
	/// Address mask reply
	Icmp_AMR = 18,
} IcmpType;

typedef struct {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t seqnum;
}__attribute__((packed)) IcmpEchoHdr;

#endif /* TIP_ICMP_HPP_ */
