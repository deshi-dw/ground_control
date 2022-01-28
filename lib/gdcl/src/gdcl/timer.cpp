#include "gdcl/timer.h"

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
#include <chrono>
#endif

namespace gdcl {

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
static bool											  is_time_started = false;
static std::chrono::high_resolution_clock::time_point start_time;
#endif

void timer::call(long interval, timer::action on_interval, void* context) {
#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	using namespace std::chrono;

	// get current time.
	auto ms = duration_cast<milliseconds>(
		high_resolution_clock::now().time_since_epoch());

	// if the current time is greater than the previous call time + the
	// interval, call again.
	if(ms.count() - prev_time > interval) {
		on_interval();
		prev_time = ms.count();
	}

#else // Arduino implementation.

	// get current time.
	auto ms = millis();

	// if the current time is greater than the previous call time + the
	// interval, call again.
	if(ms - prev_time > interval) {
		on_interval(context);
		prev_time = ms;
	}

#endif
}

long time() {
#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	using namespace std::chrono;

	// initialize the time if it hasn't already been initialized.
	if(! is_time_started) {
		start_time		= high_resolution_clock::now();
		is_time_started = true;
	}

	return duration_cast<milliseconds>(high_resolution_clock::now() -
									   start_time)
		.count();

#else // Arduino implementation.
	return millis();

#endif
}

} // namespace gdcl