inpt_map = require("config").inpt_map;

local inputs = {};

inputs.state = {};

inputs.state["button_1"] = BUTTON_UP;
inputs.state["button_2"] = BUTTON_UP;
inputs.state["button_3"] = BUTTON_UP;
inputs.state["button_4"] = BUTTON_UP;

inputs.state["left_stick_button"] = BUTTON_UP;
inputs.state["right_stick_button"] = BUTTON_UP;

inputs.state["left_bumper"] = BUTTON_UP;
inputs.state["right_bumper"] = BUTTON_UP;
inputs.state["left_back_bumper"] = BUTTON_UP;
inputs.state["right_back_bumper"] = BUTTON_UP;

inputs.state["select"] = BUTTON_UP;
inputs.state["start"] = BUTTON_UP;

inputs.state["left_trigger"] = 0.0;
inputs.state["right_trigger"] = 0.0;

inputs.state["left_stick_x"] = 0.0;
inputs.state["left_stick_y"] = 0.0;

inputs.state["right_stick_x"] = 0.0;
inputs.state["right_stick_y"] = 0.0;

inputs.process = function(e)
	-- TODO detect inpt_map type with the input devices product and vendor ids.
	local map = "xbox360";

	if(e.type == EVENT_BUTTON) then
		local key = inpt_map[map].buttons[e.id];
		inputs.state[key] = e.state;

	elseif(e.type == EVENT_AXIS) then
		local key = inpt_map[map]axis[e.id];
		inputs.state[key] = e.value;
	end
end

inputs.add = function(name, func)
	inputs[name] = func;
end

inputs.remove = function(name)
	table.remove(inputs, name);
end

return inputs;
