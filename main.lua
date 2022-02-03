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

function init()
	print("init called.");
end

function kill()
	print("kill called.");
end

local inpt = {

	--- a tabel of all the types of events there are assigned to a numerical
	--- value.
	--- (Note that the values here might not reflect the actual values assigned.)
	--- @class event_type
	event_type = {
		button = 0,
		axis = 1
	},

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
		--- ie. if `event.type == inpt.event_type.button`, then `event.button` is used.
		--- @type event_type
		type = 0,

		--- a button event. called when a button is pushed.
		--- @class event_button
		button = {
			--- the id of the button pressed.
			--- @type integer
			id = 0,

			--- the state of the button pressed.
			--- @type button_state
			state = 0
		},
		
		--- an axis event. called when an axis is moved.
		--- @class event_axis
		axis = {
			--- the id of the axis moved.
			--- @type integer
			id = 0,

			--- the value of the axis.
			--- @type number
			value = 0
		}
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

function loop()
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
function input(e)
	if(e.type == inpt.event_type.axis) then
	    
		print("axis("..tostring(e.axis.id)..")", e.axis.value);
		
		if(e.axis.id == 4) then
			bot_inpt.drive_y_up = e.axis.value;
		elseif(e.axis.id == 5) then
			bot_inpt.drive_y_down = e.axis.value;
		elseif(e.axis.id == 2) then
			bot_inpt.drive_x = e.axis.value;
		end

	elseif(e.type == inpt.event_type.button) then
	    print("button("..tostring(e.button.id)..")", e.button.state);
	end

end