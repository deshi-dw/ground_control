#include "gdcl/util.h"

#include <fstream>
#include <cstdio>

#ifdef _WIN32 // Windows includes:

#include <windows.h>

#else // Linux includes:

#include <linux/limits.h>
#include <libgen.h>
#include <unistd.h>

#endif

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

const std::string exe_path() {
#ifdef _WIN32 // Windows implementation:
// Implementation from https://stackoverflow.com/a/875264

char buffer[MAX_PATH] = { 0 };

GetModuleFileName( NULL, buffer, MAX_PATH );
size_t pos = std::string(buffer).find_last_of(L"\\/");

return std::string(buffer).substr(0, pos);

#else // Linux implementation:
// Implementation from https://stackoverflow.com/a/23943306

	char result[PATH_MAX] = {0};
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	const char *path;
	
	if (count != -1) {
		path = dirname(result);
	}

	return std::string(path);

#endif
}

bool file_exists(const std::string& path) {
	std::fstream file;
	file.open(path);

	return ! file.fail();
}

int file_write(const std::string& path, const std::string& content) {
	std::fstream file;
	
	// open and write to the file.
	file.open(path, std::fstream::trunc);
	file << content;

	// close the file.
	file.close();

	return 0;
}

int file_delete(const std::string& path) {
	if(! file_exists(path)) {
		return -1;
	}

	// delete file if it exists.
	std::remove(path.c_str());

	return 0;
}

} // namespace gdcl