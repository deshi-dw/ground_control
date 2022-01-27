#include "gdcl/net/net_stream_writer.h"

namespace gdcl {

stream_writer::stream_writer(stream& strm, endian endianess)
	: strm(strm), endianess(endianess) {
}

void stream_writer::write(const std::string& value) {
	bot_size_t size = value.size();

	write(size);
	generic_write(value.c_str(), size);
}

void stream_writer::write(uint16_t value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(uint32_t value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(uint64_t value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(int value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(long value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(float value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(double value) {
	generic_write(&value, sizeof(value), true);
}

} // namespace gdcl