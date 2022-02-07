function print_table(t, layer)
	if(layer > 20) then
		return
	end

	for k,v in pairs(t) do
		print(string.rep(' ', layer * 2) .. k, v);
		if(type(v) == "table") then
			print_table(v, layer + 1);
		end
	end
end

-- print("inpt:");
-- print_table(inpt, 1);

function gdcl_init()
	print("init called.");
end

function gdcl_kill()
	print("kill called.");
end

-- EVENT_BUTTON = 0;
-- EVENT_AXIS = 0;

-- BUTTON_NONE = 0;
-- BUTTON_DOWN = 0;
-- BUTTON_UP = 0;
-- BUTTON_HELD = 0;

local inpt = {
	--- a tabel of each possible button state assigned to a numerical value.
	--- (Note that the values here might not reflect the actual values assigned.)
	--- @class button_state
	button_state = {
		down = 0,
		up = 1
	},

	--- an input event is called whenever an input is triggered.
	--- @class event
	event = {
		--- the type of the event. This dictates which field in the event is
		--- filled in.
		type = 0,

		--- the state of the button. (only set when event type is EVENT_BUTTON)
		--- @type button_state
		state = 0,

		--- the value of the axis.
		--- @type number
		value = 0
	},

	--- an object that holds information about the input device that triggered an input.
	--- @class dev
	dev = {
		--- the dynamic id according to what order the device was plugged in.
		--- @type integer
		id = 0,

		--- the name of the device.
		--- @type string
		name = " ",

		--- the product id according to the HID spec.
		--- @type integer
		product_id = 0,

		--- the vendor id according to the HID spec.
		--- @type integer
		vendor_id = 0,

		--- an array of axis values. the index is equal to the axis id.
		--- @type table
		axis = {},

		--- an array of button state values. the index is equal to the button id.
		--- @type table
		buttons = {}
	}
};

local bot = {
	--- returns if the robot is in testing mode.
	--- @return boolean
	testing = function() end,

	--- returns if the robot is stared.
	--- @return boolean
	started = function() end,

	--- returns the time in milliseconds since the robot has been started.
	--- @return number
	time = function() end,


	--- attempts to connect both to the intercom arduino via serial and then
	--- the actual robot arduino through an nrf24l01 radio.
	--- @param baud_rate number
	---@param addr string
	connect = function(baud_rate, addr) end,

	--- sever the connection between the robot and the intercom as well as the
	--- serial connection between us and the intercom.
	disconnect = function() end,

	--- send the robots current state to the robot.
	send_state = function() end,

	--- receive new state information from the robot (if there is any).
	recive_state = function() end,

	motor_right = 0.0,
	motor_left = 0.0,
	motor_servo = 0.0
};

-- local send_timer = bot.new_timer();
-- local receive_timer = bot.new_timer();

local bot_inpt = {
	drive_y_up = 0.0,
	drive_y_down = 0.0,
	drive_x = 0.0,
};

function gdcl_loop()
	-- -- Do nothing if the robot hasn't been started.
	-- if(! bot.started()) then
	-- 	return;
	-- end

	-- --- send robot state every 20 milliseconds.
	-- send_timer.call(20, function()
	-- 	bot.send_state();
	-- end);
	
	-- --- receive robot state every 20 milliseconds.
	-- receive_timer.call(20, function()
	-- 	bot.send_state();
	-- end);

	-- -- if the robot is in testing mode, run the testing couroutine.
	-- if(bot.testing()) then
	-- 	testing();
	-- 	return;
	-- end

	-- -- run 30 seconds of the autonomous couroutine:
	-- if(bot.time() <= 30000) then
	-- 	autonomous();
	-- else
	-- 	-- run user controlled couroutine.
	-- 	teleop();
	-- end
end

function testing()
end

function autonomous()
end

function teleop()
	
end

---@param e event
---@param dev dev
function gdcl_input(dev, e)
	-- print_table(dev, 1);

	local dev_str = "["..tostring(dev.id).."] "..dev.name..": ";
	local event_str = "";

	if(e.type == EVENT_BUTTON) then
		event_str = "button ";

		if(e.state == BUTTON_DOWN) then
			event_str = event_str.."DOWN";
		elseif(e.state == BUTTON_UP) then
			event_str = event_str.."UP";
		elseif(e.state == BUTTON_HELD) then
			event_str = event_str.."HELD";
		end
	elseif (e.type == EVENT_AXIS) then
		event_str = "axis ";
		event_str = event_str..(tostring(e.value));
	end

	print(dev_str..event_str);
end