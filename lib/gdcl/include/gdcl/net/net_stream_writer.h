#ifndef GDCL_NET_STREAM_WRITER_H
#define GDCL_NET_STREAM_WRITER_H

#include "gdcl/util.h"
#include "gdcl/net/net.h"

#include <string>

namespace gdcl {
namespace net {

struct stream_writer {
	typedef uint16_t bot_size_t;

	stream& stream;
	endian	endianess;

	stream_writer(net::stream& stream, endian endianess);

	void write(const uint16_t& value);
	void write(const uint32_t& value);
	void write(const uint64_t& value);
	void write(const std::string& value);

	template <typename T> void write(T& value);

	template <typename T> void generic_write(T* value, bot_size_t size);
};

template <typename T> void stream_writer::write(T& value) {
	generic_write(&value, sizeof(value));
}

template <typename T>
void stream_writer::generic_write(T* value, bot_size_t size) {
	stream.write((void*) value, size);
}

} // namespace net
} // namespace gdcl

#endif
