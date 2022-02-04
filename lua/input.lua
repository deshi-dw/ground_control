inpt_map = require("config").inpt_map;

local inputs = {};

inputs.state = {};

inputs.state["button_1"] = BUTTON_NONE;
inputs.state["button_2"] = BUTTON_NONE;
inputs.state["button_3"] = BUTTON_NONE;
inputs.state["button_4"] = BUTTON_NONE;

inputs.state["left_stick_button"] = BUTTON_NONE;
inputs.state["right_stick_button"] = BUTTON_NONE;

inputs.state["left_bumper"] = BUTTON_NONE;
inputs.state["right_bumper"] = BUTTON_NONE;
inputs.state["left_back_bumper"] = BUTTON_NONE;
inputs.state["right_back_bumper"] = BUTTON_NONE;

inputs.state["select"] = BUTTON_NONE;
inputs.state["start"] = BUTTON_NONE;

inputs.state["left_trigger"] = 0.0;
inputs.state["right_trigger"] = 0.0;

inputs.state["left_stick_x"] = 0.0;
inputs.state["left_stick_y"] = 0.0;

inputs.state["right_stick_x"] = 0.0;
inputs.state["right_stick_y"] = 0.0;

inputs.process = function(e)
	-- TODO detect inpt_map type with the input devices product and vendor ids.
	if(e.type == EVENT_BUTTON) then
		local key = inpt_map["xbox360"].buttons[e.id];
		-- FIXME this wont work because it only updates when there is a button_1
		--       press / release. rework to work without needing constant
		--       updates.
		if(inputs.state[key] == BUTTON_NONE) then
			inputs.state[key] = e.state == 1 ? BUTTON_DOWN : BUTTON_UP;
		elseif(inputs.state[key] == BUTTON_DOWN
			   or inputs.state[key] == BUTTON_HELD) then
			inputs.state[key] = e.state == 1 ? BUTTON_HELD : BUTTON_UP;
		elseif(inputs.state[key] == BUTTON_UP) then
			inputs.state[key] = e.state == 1 ? BUTTON_DOWN : BUTTON_UP;
		end
	end
end

inputs.add = function(name, func)
	inputs[name] = func;
end

inputs.remove = function(name)
	table.remove(inputs, name);
end

return inputs;
