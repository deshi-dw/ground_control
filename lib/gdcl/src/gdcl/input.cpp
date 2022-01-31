#include "gdcl/input.h"

#include "gamepad/Gamepad.h"

// gamepad/Gamepad.h defines bool as int and doesn't undefine it which fucks
// with some code further down.
#undef bool

namespace gdcl {
namespace inpt {

std::unordered_map<unsigned int, dev> devices;

std::function<void(dev&, int, button_state)> on_button;
std::function<void(dev&, int, float)>		 on_axis;

std::function<void(dev&, event)> on_input;

static std::unordered_map<unsigned int, Gamepad_device*> raw_devices;

const static int detect_dev_interval = 1000;
static int		 detect_dev_timer	 = 0;

static bool is_initialized = false;

static void on_dev_attach(struct Gamepad_device* device, void* context) {
	raw_devices[device->deviceID] = device;

	// create a new device struct.
	devices[device->deviceID] = {device->deviceID,
								 std::string(device->description),
								 device->vendorID,
								 device->productID,
								 std::vector<float>(device->numAxes),
								 std::vector<bool>(device->numButtons)};
}

static void on_dev_remove(struct Gamepad_device* device, void* context) {
	// remove device from device map.
	devices.erase(device->deviceID);
}

static void on_btn_down(struct Gamepad_device* device, unsigned int buttonID,
						double timestamp, void* context) {
	// if the device doesn't exist in the device map, don't try to update it.
	if(devices.find(device->deviceID) == devices.end()) {
		return;
	}

	// call global button event.
	if(on_button) {
		on_button(devices[device->deviceID], buttonID, button_state::down);
	}

	// call global on input event.
	if(on_input) {
		on_input(devices[device->deviceID],
				 (event){event::type::button,
						 .button = {buttonID, button_state::down}});
	}

	// call local button event.
	if(devices[device->deviceID].on_button != nullptr) {
		devices[device->deviceID].on_button(buttonID, button_state::down);
	}
}

static void on_btn_up(struct Gamepad_device* device, unsigned int buttonID,
					  double timestamp, void* context) {
	// if the device doesn't exist in the device map, don't try to update it.
	if(devices.find(device->deviceID) == devices.end()) {
		return;
	}

	// call global button event.
	if(on_button) {
		on_button(devices[device->deviceID], buttonID, button_state::up);
	}

	// call global on input event.
	if(on_input) {
		on_input(devices[device->deviceID],
				 (event){event::type::button,
						 .button = {buttonID, button_state::up}});
	}

	// call local button event.
	if(devices[device->deviceID].on_button != nullptr) {
		devices[device->deviceID].on_button(buttonID, button_state::up);
	}
}

static void on_axis_move(struct Gamepad_device* device, unsigned int axisID,
						 float value, float lastValue, double timestamp,
						 void* context) {
	// if the device doesn't exist in the device map, don't try to update it.
	if(devices.find(device->deviceID) == devices.end()) {
		return;
	}

	// call global axis event.
	if(on_axis) {
		on_axis(devices[device->deviceID], axisID, value);
	}

	// call global on input event.
	if(on_input) {
		on_input(devices[device->deviceID],
				 (event){event::type::axis, .axis = {axisID, value}});
	}

	// call local axis event.
	if(devices[device->deviceID].on_axis != nullptr) {
		devices[device->deviceID].on_axis(axisID, value);
	}
}

int init() {
	Gamepad_deviceAttachFunc(on_dev_attach, (void*) 0x1);
	Gamepad_deviceRemoveFunc(on_dev_remove, (void*) 0x2);

	Gamepad_axisMoveFunc(on_axis_move, (void*) 0x3);
	Gamepad_buttonDownFunc(on_btn_down, (void*) 0x4);
	Gamepad_buttonUpFunc(on_btn_up, (void*) 0x5);

	Gamepad_init();

	return 0;
}

int deinit() {
	Gamepad_shutdown();

	return 0;
}

int poll() {
	// don't run detect devices every time poll is called because it seems kinda
	// expensive.
	if(detect_dev_timer <= 0) {
		Gamepad_detectDevices();
		detect_dev_timer = detect_dev_interval;
	}
	else {
		detect_dev_timer--;
	}

	Gamepad_processEvents();

	// update device button and axis values.
	for(auto dev : devices) {
		Gamepad_device* raw_dev = raw_devices[dev.second.id];

		for(int i = 0; i < raw_dev->numAxes; i++) {
			devices[raw_dev->deviceID].axises[i] = raw_dev->axisStates[i];
		}

		for(int i = 0; i < raw_dev->numButtons; i++) {
			devices[raw_dev->deviceID].buttons[i] = raw_dev->buttonStates[i];
		}
	}

	return 0;
}

} // namespace inpt
} // namespace gdcl