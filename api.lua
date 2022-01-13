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
	serial = serial.new("/dev/ttyUSB0", 9600);
end

function bot:kill()
	serial.close();
end

function bot:loop()
end

--[[ c++

gdcl::bot bot;
gdcl::rs rs;

bot.connect();

while(1) {
	rs.update();
}

]]--
