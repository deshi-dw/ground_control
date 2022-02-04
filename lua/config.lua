local cfg = {};

--       left_trigger /        right_trigger /
--  ████ left_back_bumper  ████ right_back_bumper
--
--     ┌─ left_bumper         ┌─ right_bumper
--  ▒█████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▒
-- ▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒
-- ▒▒▄▄▒▒▒▒▒▒▒█▒▒▒▒▒▒▒█▒▒▒▒▒4▒▒▒▒
-- ▒▐██▌▒▒▒select▒▒▒start▒1▒▒▒3▒▒
-- ▒▒▀▀▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▄▄▒▒▒2▒▒▒▒
-- ▒▒▒│▒▒███▒▒▒▒▒▒▒▒▒▒▐██▌▒▒▒▒▒▒▒
-- ▒▒▒│▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒
-- ▒▒▒│▒  └ dpad        │   ▒▒▒▒▒
--  ▒▒│                 │    ▒▒▒
--    └ right_stick_x / └ left_stick_x /
--      left_stick_y      left_stick_y

local dual_action_map = {
	buttons = {
		[0] = "button_1",
		[1] = "button_2",
		[2] = "button_3",
		[3] = "button_4",

		[10] = "left_stick_button",
		[11] = "right_stick_button",

		[4] = "left_bumper",
		[5] = "right_bumper",
		[6] = "left_back_bumper",
		[7] = "right_back_bumper",

		[8] = "select",
		[9] = "start",
	},s
	axis = {
		[0] = "left_stick_x",
		[1] = "left_stick_y",

		[2] = "right_stick_x",
		[3] = "right_stick_y",
	}
};

local xbox360_map = {
	buttons = {
		[2] = "button_1",
		[0] = "button_2",
		[1] = "button_3",
		[3] = "button_4",

		[10] = "left_stick_button",
		[11] = "right_stick_button",

		[4] = "left_bumper",
		[5] = "right_bumper",

		[6] = "select",
		[7] = "start",
	},
	axis = {
		[2] = "left_trigger",
		[5] = "right_trigger",

		[0] = "left_stick_x",
		[1] = "left_stick_y",

		[3] = "right_stick_x",
		[4] = "right_stick_y",
	}
};

-- TODO add proper product and vendor ids so the gamepad can be automatically
--      detected.
cfg.inpt_map = {
	["dual_action"] = { pid = 0, vid = 0, map = dual_action_map },
	["xbox360"] = { pid = 0, vid = 0, map = xbox360_map },
};

cfg.bot = {
	speed_drive = 1.0,
	speed_turn = 1.0
};

cfg.inputs = {
	drive_forwards  = "right_trigger",
	drive_backwards = "left_trigger",

	turn = "right_stick_x"
};

cfg.autonomous_time = 30000;     -- 30 seconds of autonomous.
cfg.game_time = 180000;          -- 3 minutes game time.

cfg.send_state_interval = 20;    -- 20 milliseconds per state send.
cfg.receive_state_interval = 20; -- 20 milliseconds per state receive.

return cfg;
