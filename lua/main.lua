local cfg = require("cfg")
local drive = require("drive")

function loop()
	-- Do nothing if the robot hasn't been started.
	if(! bot.started()) then
		return;
	end

	--- send robot state every 20 milliseconds.
	send_timer.call(cfg.send_state_interval, function()
		bot.send_state();
	end);

	--- receive robot state every 20 milliseconds.
	receive_timer.call(cfg.receive_state_interval, function()
		bot.send_state();
	end);

	-- if the robot is in testing mode, run the testing couroutine.
	if(bot.testing()) then
		testing();
		return;
	end

	-- run 30 seconds of the autonomous couroutine:
	if(bot.time() <= cfg.autonomous_time) then
		autonomous();
	else if(bot.time() <= cfg.game_time)
		-- run user controlled couroutine.
		teleop();
	else
		disabled();
	end
end

function testing()
end

function autonomous()
end

function teleop()
	input.on_down("button_4", function()
		-- routines could be simple little loops that return false until they
		-- meet a desired condition in which case they return true.

		-- main loop: foreach r in routines: r.is_finished = r.func(r.state)
		routines["lift_cube"] = {
			state = {},
			func = function(state)
				lift.set(1.0);

				return lift.get() > 0.99;
			end
		};
	end);
end

function disabled()
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
