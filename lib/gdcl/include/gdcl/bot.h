#ifndef GDCL_BOT_H
#define GDCL_BOT_H

#include "gdcl/net/net_serial.h"

namespace gdcl {

struct bot {
	private:
	gdcl::serial serial;

	enum class packet_id : uint8_t {
		null,
		connect,
		disconnect,
		print,
		set_motors,
		get_motors
	};

	public:
	struct motors_t {
		float right;
		float left;
	};

	void connect(const std::string& port, int baud_rate,
				 const std::string& addr);
	void disconnect();

	bool is_connected();

	void print(const std::string& str);

	void set_motors(motors_t motors);
	motors_t get_motors();
};

} // namespace gdcl

#endif