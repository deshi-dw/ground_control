#include "gdcl/util.h"

namespace gdcl {

endian system_endian() {
#if defined(ARDUINO) // Arduino implementation:
	return endian::little;
#endif

	int num = 1;
	if(*(char*) &num == 1) {
		return endian::little;
	}
	else {
		return endian::big;
	}
}

} // namespace gdcl