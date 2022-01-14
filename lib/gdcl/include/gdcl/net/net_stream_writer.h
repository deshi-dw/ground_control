#ifndef GDCL_NET_STREAM_WRITER_H
#define GDCL_NET_STREAM_WRITER_H

#include "gdcl/util.h"
#include "gdcl/net/net.h"

#include <string>

namespace gdcl {

struct stream_writer {
	typedef uint16_t bot_size_t;

	stream& strm;
	endian	endianess;

	stream_writer(stream& strm, endian endianess = endian::little);

	void write(const uint16_t value);
	void write(const uint32_t value);
	void write(const uint64_t value);

	void write(const std::string& value);

	template <typename T> void write(T& value);

	template <typename T>
	void generic_write(T* value, bot_size_t size, bool endian_aware = false);
	void generic_write(uint16_t* value, bot_size_t size);
	void generic_write(uint32_t* value, bot_size_t size);
	void generic_write(uint64_t* value, bot_size_t size);
};

template <typename T> void stream_writer::write(T& value) {
	generic_write(&value, sizeof(value));
}

template <typename T> void
	stream_writer::generic_write(T* value, bot_size_t size, bool endian_aware) {
	if(! endian_aware) {
		strm.write((void*) value, size);
	}
	else {
		strm.write(
			(void*) (system_endian() != endianess ? swap_endian(value) : value),
			size);
	}
}

} // namespace gdcl

#endif
