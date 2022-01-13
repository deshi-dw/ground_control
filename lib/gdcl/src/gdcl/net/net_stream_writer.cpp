#include "gdcl/net/net_stream_writer.h"

namespace gdcl {
namespace net {

stream_writer::stream_writer(net::stream& stream, endian endianess)
	: stream(stream), endianess(endianess) {
}

void stream_writer::write(const uint16_t& value) {
	uint16_t new_value =
		system_endian() != endianess ? swap_endian(value) : value;
	generic_write(&new_value, sizeof(value));
}
void stream_writer::write(const uint32_t& value) {
	uint32_t new_value =
		system_endian() != endianess ? swap_endian(value) : value;
	generic_write(&new_value, sizeof(value));
}
void stream_writer::write(const uint64_t& value) {
	uint64_t new_value =
		system_endian() != endianess ? swap_endian(value) : value;
	generic_write(&new_value, sizeof(value));
}

void stream_writer::write(const std::string& value) {
	bot_size_t size = value.size();

	write(size);
	generic_write(value.c_str(), size);
}

} // namespace net
} // namespace gdcl