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

	void write(const std::string& value);
	void write(uint16_t value);
	void write(uint32_t value);
	void write(uint64_t value);
	void write(int value);
	void write(long value);
	void write(float value);
	void write(double value);

	template <typename T>
	void generic_write(T* value, bot_size_t size, bool endian_aware = false);
};

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
