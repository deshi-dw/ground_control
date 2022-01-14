#include "gdcl/net/net.h"

#include "gdcl/net/packets.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace gdcl {

// TODO add a stream reader that can do all sorts of cool things like read until
// the next \n character and other stuffs.

// FIXME add stream checks for out of bounds read / writes.

stream::stream(size_t buffer_size) {
	buffer = (uint8_t*) calloc(buffer_size, 1);
	size   = buffer_size;
	reset();
}

stream::stream() {
	stream(256);
}

stream::~stream() {
	free(buffer);
}

void stream::reset() {
	start = buffer;
	end	  = buffer;
}

void stream::seek(size_t index) {
	start = buffer + index;
}

size_t stream::count() {
	return end - buffer;
}

int stream::read(void* data, size_t size) {
	int i = 0;

	uint8_t* stop = start + size;

	while(start + i != stop) {
		((uint8_t*) data)[i] = start[i];
		i++;
	}

	start = stop;

	return i;
}

int stream::write(void* data, size_t size) {
	end = start + size;

	int i = 0;
	while(start + i != end) {
		start[i] = ((uint8_t*) data)[i];
		i++;
	}

	start = end;

	return i;
}

radio::radio() : in(256), out(256) {
}

int test_radio::pull() {
	uint8_t data[32];
	int		count		= remote->out.count();
	int		segments	= count / sizeof(data);
	int		extra_bytes = count % sizeof(data);

	if(count <= 0) {
		return -1;
	}

	// read remote's output and put the data into the host's input buffer.
	for(int i = 0; i < segments; i++) {
		remote->out.read(data, sizeof(data));
		in.write(data, sizeof(data));
	}

	// pull any remaining bytes if the packet didn't perfectly divide into 32
	// byte segments.
	if(extra_bytes != 0) {
		memset(data, 0, sizeof(data));
		remote->out.read(data, extra_bytes);
		in.write(data, sizeof(data));
	}

	in.seek(0);
	remote->out.seek(0);

	return 0;
}

int test_radio::push() {
	uint8_t data[32];
	int		count		= out.count();
	int		segments	= count / sizeof(data);
	int		extra_bytes = count % sizeof(data);

	if(count <= 0) {
		return -1;
	}

	// read from the host's output buffer and put the bytes into the remote's
	// input buffer.
	for(int i = 0; i < segments; i++) {
		out.read(data, sizeof(data));
		remote->in.write(data, sizeof(data));
	}

	// push any remaining bytes if the packet didn't perfectly divide into 32
	// byte segments.
	if(extra_bytes != 0) {
		memset(data, 0, sizeof(data));
		out.read(data, extra_bytes);
		remote->in.write(data, sizeof(data));
	}

	out.seek(0);
	remote->in.seek(0);

	return 0;
}

} // namespace gdcl