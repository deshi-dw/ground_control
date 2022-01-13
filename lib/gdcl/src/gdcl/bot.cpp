#include "gdcl/bot.h"

void gdcl::bot::connect(const std::string& port, int baud_rate,
						const std::string& addr) {
	// try to open a serial connection to whatever communication device we are
	// using to communicate to and from the robot.
	if(serial.open(port.c_str(), baud_rate) != 0) {
		throw std::runtime_error("failed to connect to the robot: couldn't "
								 "open a serial connection.");
	}
}