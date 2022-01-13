#ifndef GDCL_BOT_H
#define GDCL_BOT_H

#include "gdcl/net/net_serial.h"

namespace gdcl {

struct bot {
	private:
	net::serial serial;

	public:
	void connect(const std::string& port, int baud_rate,
				 const std::string& addr);
	void disconnect();

	bool is_connected();

	void set_motors(float dc, float servo);

	float get_dc();
	float get_servo();
}

} // namespace gdcl

#endif