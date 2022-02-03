local cfg = require(config)

local drive = {
	speed_turn = 1.0,
	speed_drive = 1.0
};

drive.tank = function(right, left)
	-- calculate the offsets of speed values and multiply them by the side
	-- speeds.
	local right = (1 + self.speed_r_off) * right;
	local left = (1 + self.speed_l_off) * left;

	-- set motor speeds.
	bot.right = right;
	bot.left = left;
end

drive.arcade = function(speed, turn, range)
	-- clamp speed and turn values to the given range.
	local x = math.max(-range, math.min(turn, range));
	local y = math.max(-range, math.min(speed, range));

	-- multiply speed and turn values by the drivetrain's speed and turn
	-- multipliers.
	x = x * cfg.bot.speed_turn;
	y = y * cfg.bot.speed_drive;

	-- the formula used here was gotten from the following article:
	-- https://home.kendra.com/mauser/Joystick.html

	-- calculate the right + left speed.
	local v = (range - math.abs(x)) * (y / range) + y;

	-- calculate the right - left speed.
	local w = (range - math.abs(y)) * (x / range) + x;

	-- extract both the right and left speeds.
	local right = (v + w) / 2;
	local left = (v - w) / 2;

	drive.drive_tank(right, left);
end

return drive;
