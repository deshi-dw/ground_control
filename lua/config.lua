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
	["button_1"] = 0,
	["button_2"] = 1,
	["button_3"] = 2,
	["button_4"] = 3,

	["right_stick_button"] = 11,
	["left_stick_button"] = 10,

	["left_bumper"] = 4,
	["right_bumper"] = 5,
	["left_back_bumper"] = 6,
	["right_back_bumper"] = 7,

	["select"] = 8,
	["start"] = 9,

	["left_stick_x"] = 0,
	["left_stick_y"] = 1,

	["right_stick_x"] = 2,
	["right_stick_y"] = 3,
};

local xbox360_map = {
	["button_1"] = 2,
	["button_2"] = 0,
	["button_3"] = 1,
	["button_4"] = 3,

	["right_stick_button"] = 11,
	["left_stick_button"] = 10,

	["left_bumper"] = 4,
	["right_bumper"] = 5,

	["left_trigger"] = 2,
	["right_trigger"] = 5,

	["start"] = 7,
	["select"] = 6,

	["left_stick_x"] = 0,
	["left_stick_y"] = 1,

	["right_stick_x"] = 3,
	["right_stick_y"] = 4,
};

cfg.inpt_map = {
	["dual_action"] = dual_action_map,
	["xbox360"] = xbox360_map
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
