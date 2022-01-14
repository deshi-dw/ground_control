#include "gdcl/net/net_stream_writer.h"

namespace gdcl {

stream_writer::stream_writer(stream& strm, endian endianess)
	: strm(strm), endianess(endianess) {
}

void generic_write(uint16_t* value, stream_writer::bot_size_t size) {
	// TODO pick up where you left off.
	generic_write<uint16_t>(value, sizeof(decltype(value)), true);
}
void generic_write(uint32_t* value, stream_writer::bot_size_t size) {
}
void generic_write(uint64_t* value, stream_writer::bot_size_t size) {
}

void stream_writer::write(const uint16_t value) {
	// uint16_t new_value =
	// 	system_endian() != endianess ? swap_endian(value) : value;
	// generic_write(&new_value, sizeof(value));
	generic_write(&value, sizeof(value), true);
}
void stream_writer::write(const uint32_t value) {
	generic_write(&value, sizeof(value), true);
}
void stream_writer::write(const uint64_t value) {
	generic_write(&value, sizeof(value), true);
}

void stream_writer::write(const std::string& value) {
	bot_size_t size = value.size();

	write(size);
	generic_write(value.c_str(), size);
}

} // namespace gdcl