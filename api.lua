local serial = serial.new("/dev/ttyUSB0", 9600);
local input = input.new(0);

input.add('drive_y', {
	value = function()
		return input:axis('right_trigger') - input:axis('left_trigger');
	end,
	modifier = function(value)
		input:slope('')
	end
});

function bot:init()
	bot.connect("/dev/ttyUSB0", 9600);
	bot.print("Hello, world.");
end

function bot:kill()
	bot.disconnect();
end

function bot:loop()
	bot.set_motors(1.0, 1.0);
end

function inpt:axis(value)
end

function inpt:button(state)
end

--[[ c++

gdcl::bot bot;
gdcl::rs rs;

bot.connect();

while(1) {
	rs.update();
}

]]--
