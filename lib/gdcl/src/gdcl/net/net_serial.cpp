#include "gdcl/net/net_serial.h"

#if ! defined(ARDUINO)
#include "serialib.h"
#else
#include "Arduino.h"
#endif

namespace gdcl {

int serial::open(const char* port, int baud_rate) {
#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	if(serial.isDeviceOpen()) {
		return -1;
	}

	if(serial.openDevice(port, baud_rate) != 1) {
		return -1;
	}
#else // Arduino implementation.
	if(Serial) {
		Serial.end();
	}

	Serial.begin(baud_rate);
#endif

	return 0;
}

int serial::close() {
#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	if(! serial.isDeviceOpen()) {
		return -1;
	}

	serial.closeDevice();
#else // Arduino implementation.
	if(! Serial) {
		return -1;
	}

	Serial.end();
#endif

	return 0;
}

bool serial::is_open() {
	return serial.isDeviceOpen();
}

int serial::pull() {
#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	int read_size = serial.available();
#else // Arduino implementation.
	int read_size = Serial.available();
#endif

	// don't read more than we can store.
	if(read_size > in.size) {
		read_size = in.size;
	}

	uint8_t data[read_size];

// read all the incoming bytes from the serial connection.
#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	serial.readBytes(data, read_size, 0);
#else // Arduino implementation.
	for(int i = 0; i < read_size; i++) {
		int incoming = Serial.read();
		if(incoming <= 0) {
			read_size = i;
			break;
		}

		data[i] = incoming;
	}
#endif

	// write incoming serial data to in stream.
	out.seek(0);
	in.write(data, read_size);

	// reset in buffer.
	// TODO think about restoring the previous start index instead.
	in.seek(0);

	return read_size;
}

int serial::push() {
	size_t	write_size = out.count();
	uint8_t data[write_size];

	// read out data to a buffer and then write it to serial.
	// FIXME: out is reading zeros (I think)
	out.seek(0);
	out.read(data, write_size);

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	serial.writeBytes(data, write_size);
#else // Arduino implementation.
	Serial.write(data, write_size);
#endif

	// reset out buffer.
	// TODO think about restoring the previous start index instead.
	out.seek(0);

	return write_size;
}

} // namespace gdcl
