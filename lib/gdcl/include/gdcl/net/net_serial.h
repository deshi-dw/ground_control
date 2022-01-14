#ifndef BOT_NET_SERIAL_H
#define BOT_NET_SERIAL_H

#include "net.h"

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
#include "serialib.h"
#endif

namespace gdcl {

struct serial : radio {

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	serialib serial;
#endif

	int open(const char* port, int baud_rate);
	int close();

	bool is_open();

	int pull() override;
	int push() override;
};

} // namespace gdcl

#endif