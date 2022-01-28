#ifndef GDCL_TIMER_H
#define GDCL_TIMER_H

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
#include <functional>
#endif

namespace gdcl {

struct timer {
	// if we're programming on pc, we can use the nice std::function wrapper for
	// lambda and such. On Arduino however there is no std::function so we need
	// to used a function pointer instead. This means we can't use capturing
	// lambdas as an argument in the arduino code which is annyoing but
	// whatever.

#if ! defined(ARDUINO) // Windows, Linux, and Mac implementation.
	typedef std::function<void()> action;
#else // Arduino implementation.
	typedef void (*action)(void* context);
#endif

	long prev_time = 0;

	void call(long interval, action on_interval, void* context = nullptr);
};

long time();

} // namespace gdcl

#endif