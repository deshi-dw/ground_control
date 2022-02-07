#include "gdcl/input.h"

#include "gamepad/Gamepad.h"
#include "gdcl/timer.h"

// gamepad/Gamepad.h defines bool as int and doesn't undefine it which fucks
// with some code further down.
#undef bool

namespace gdcl {
namespace inpt {

std::unordered_map<unsigned int, dev> devices;

std::function<void(dev&, event)> on_input;

static std::unordered_map<unsigned int, Gamepad_device*> raw_devices;

const static int detect_dev_interval = 1000;
static timer	 detect_dev_timer;

static timer button_state_change_timer;

static bool is_initialized = false;

static void on_dev_attach(struct Gamepad_device* device, void* context) {
	raw_devices[device->deviceID] = device;

	// create a new device struct.
	devices[device->deviceID] = {device->deviceID,
								 std::string(device->description),
								 device->vendorID,
								 device->productID,
								 std::vector<float>(device->numAxes),
								 std::vector<button_state>(device->numButtons)};
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

	button_state state = button_state::down;

	// update device button state.
	devices[device->deviceID].buttons[buttonID] = state;

	// call global on input event.
	if(on_input) {
		on_input(devices[device->deviceID],
				 (event){event::type::button, buttonID, {.state = state}});
	}
}

static void on_btn_up(struct Gamepad_device* device, unsigned int buttonID,
					  double timestamp, void* context) {
	// if the device doesn't exist in the device map, don't try to update it.
	if(devices.find(device->deviceID) == devices.end()) {
		return;
	}

	button_state state = button_state::up;

	// update device button state.
	devices[device->deviceID].buttons[buttonID] = state;

	// call global on input event.
	if(on_input) {
		on_input(devices[device->deviceID],
				 (event){event::type::button, buttonID, {.state = state}});
	}
}

static void on_axis_move(struct Gamepad_device* device, unsigned int axisID,
						 float value, float lastValue, double timestamp,
						 void* context) {
	// if the device doesn't exist in the device map, don't try to update it.
	if(devices.find(device->deviceID) == devices.end()) {
		return;
	}

	// TODO I commented this out because I'm not sure if it is really needed but
	//      I think it is worth comparing weither or not this is benificial.

	//	// don't update axis if the distance moved is too little.
	// 	if(std::abs(value - devices[device->deviceID].axis[axisID]) < 0.01f) {
	// 		return;
	// 	}

	// update device axis vaule.
	devices[device->deviceID].axis[axisID] = value;

	// call global on input event.
	if(on_input) {
		on_input(devices[device->deviceID],
				 (event){event::type::axis, axisID, {.value = value}});
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
	detect_dev_timer.call(detect_dev_interval, []() {
		Gamepad_detectDevices();
	});

	// update button state every 5 ms. Note that this is only for changes like
	// BUTTON_DOWN -> BUTTON_HELD and BUTTON_UP -> BUTTON_NONE.
	button_state_change_timer.call(5, [&]() {
		for(auto dev_pair : devices) {
			dev& dev = devices[dev_pair.first];

			// update the state of the buttons to include states none and held.
			for(int i = 0; i < dev.buttons.size(); i++) {
				switch(dev.buttons[i]) {
					case button_state::up:
						dev.buttons[i] = button_state::none;
						break;
					case button_state::down:
						dev.buttons[i] = button_state::held;
						break;
					case button_state::held:
						// repeatedly call on_input while a button is held.
						if(on_input) {
							event e = {event::type::button, (unsigned) i,
									   dev.buttons[i]};
							on_input(dev, e);
						}
						break;

					default:
						break;
				}
			}
		}
	});

	// process input device events.
	Gamepad_processEvents();

	return 0;
}

} // namespace inpt
} // namespace gdcl
