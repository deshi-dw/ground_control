#ifndef GDCL_INPUT_H
#define GDCL_INPUT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

namespace gdcl {
namespace inpt {

enum class button_state : uint8_t {
	down,
	up
};

struct dev {
	unsigned int id;
	std::string	 name;

	int vendor_id;
	int product_id;

	std::vector<float> axises;
	std::vector<bool>  buttons;

	std::function<void(int, button_state)> on_button;
	std::function<void(int, float)>  on_axis;
};

extern std::unordered_map<unsigned int, dev> devices;

extern std::function<void(dev&, int, button_state)> on_button;
extern std::function<void(dev&, int, float)>  on_axis;

int init();
int deinit();

int poll();

} // namespace inpt
} // namespace gdcl

#endif
