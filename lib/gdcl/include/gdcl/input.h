#ifndef GDCL_INPUT_H
#define GDCL_INPUT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

namespace gdcl {
namespace inpt {

enum class button_state : uint8_t { none, up, down, held };

struct dev {
	unsigned int id;
	std::string	 name;

	int vendor_id;
	int product_id;

	std::vector<float> axis;
	std::vector<button_state>  buttons;
};

struct event {
	enum class type { button, axis };

	event::type  type;
	unsigned int id;

	union {
		button_state state;
		float        value;
	};
};

extern std::unordered_map<unsigned int, dev> devices;

extern std::function<void(dev&, event)> on_input;

int init();
int deinit();

int poll();

} // namespace inpt
} // namespace gdcl

#endif
