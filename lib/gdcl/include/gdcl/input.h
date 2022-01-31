#ifndef GDCL_INPUT_H
#define GDCL_INPUT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

namespace gdcl {
namespace inpt {

enum class button_state : uint8_t { down, up };

struct dev {
	unsigned int id;
	std::string	 name;

	int vendor_id;
	int product_id;

	std::vector<float> axises;
	std::vector<bool>  buttons;

	std::function<void(int, button_state)> on_button;
	std::function<void(int, float)>		   on_axis;
};

struct event_button {
	unsigned		   id;
	inpt::button_state state;
};

struct event_axis {
	unsigned id;
	float	 value;
};

// TODO event can be simplified by moving id out of event_button and event_axis
//      and just have state / value unionized.
//      However, I'm concerned that if we add more event type like keyboard /
//      mouse that it wouldn't scale as well.
struct event {
	enum class type { button, axis };

	event::type type;

	union {
		event_button button;
		event_axis	 axis;
	};
};

extern std::unordered_map<unsigned int, dev> devices;

extern std::function<void(dev&, int, button_state)> on_button;
extern std::function<void(dev&, int, float)>		on_axis;

extern std::function<void(dev&, event)> on_input;

int init();
int deinit();

int poll();

} // namespace inpt
} // namespace gdcl

#endif
