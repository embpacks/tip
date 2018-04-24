//============================================================================
// Name        : tip.cpp
// Author      : Teja
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdint.h>
#include <iostream>
#include "tip/tip.h"

using namespace std;

enum {
	IpMaxTelSize = 1500, IpHeaderSize = 20, IpMaxDataSize = IpMaxTelSize
			- IpHeaderSize,
};

int main() {
	Ip4Addr loc = Ip4Addr::loopback;
	cout << loc << endl;
	Ip4Addr mask = Ip4Addr(0xffff0000);
	loc = loc.network(mask);
	cout << loc << endl;
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
