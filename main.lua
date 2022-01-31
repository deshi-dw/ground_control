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

function loop()
	-- print("hello, world.");
end

function input(e)
	if(e.type == inpt.event_type.axis) then
	    print("axis("..tostring(e.axis.id)..")", e.axis.value);
	elseif(e.type == inpt.event_type.button) then
	    print("button("..tostring(e.button.id)..")", e.button.state);
	end
end