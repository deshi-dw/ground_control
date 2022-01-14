#include "gdcl/bot.h"
#include "gdcl/net/net_stream_writer.h"

namespace gdcl {

void bot::connect(const std::string& port, int baud_rate,
				  const std::string& addr) {
	// try to open a serial connection to whatever communication device we are
	// using to communicate to and from the robot.
	if(serial.open(port.c_str(), baud_rate) != 0) {
		throw std::runtime_error("failed to connect to the robot: couldn't "
								 "open a serial connection.");
	}

	// TODO send connection message.
}

void bot::disconnect() {
	// TODO send disconnect message.

	if(! serial.is_open()) {
		throw std::runtime_error(
			"failed to disconnect from the robot: serial connection isn't open.");
	}

	if(serial.close() != 0) {
		throw std::runtime_error("failed to disconnect from the robot: serial couldn't close.");
	}
}

void bot::print(const std::string& str) {
	stream_writer writer(serial.out);
	writer.write(str + '\n');
	serial.push();
}

void bot::set_motors(motors_t motors) {
	stream_writer writer(serial.out);
	writer.write(static_cast<uint8_t>(packet_id::set_motors));
	writer.write(motors.right);
	writer.write(motors.left);
	serial.push();
}

bot::motors_t bot::get_motors() {
	return {0};
}

} // namespace gdcl