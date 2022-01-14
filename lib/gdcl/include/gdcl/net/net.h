#ifndef BOT_NET_H
#define BOT_NET_H

#include <stddef.h>
#include <stdint.h>

namespace gdcl {
struct stream {
	uint8_t* start;
	uint8_t* end;
	uint8_t* buffer;

	size_t size;

	stream(size_t buffer_size);
	stream();

	~stream();

	void reset();
	void seek(size_t index);
	size_t count();

	int read(void* data, size_t size);
	int write(void* data, size_t size);
};

struct radio {
	stream in;
	stream out;

	radio();

	virtual int pull() = 0;
	virtual int push() = 0;
};

struct test_radio : radio {
	radio* remote;

	int pull() override;
	int push() override;
};

} // namespace gdcl

#endif
