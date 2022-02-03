#include "gdcl/script.h"

#include "gdcl/util.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>

namespace gdcl {
namespace script {

static sol::state lua;

std::function<void()>			 func_init;
std::function<void()>			 func_kill;
std::function<void()>			 func_loop;
std::function<void(inpt::event)> func_input;

// TODO redefine print function to redirect it.

int load(const std::string& config_path) {
	// use math and coroutine libraries to make life easier.
	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					   sol::lib::coroutine, sol::lib::debug);

	// TODO think about loading the config after the api so we can use api
	// things in the config file.

	// load config file if it exists.
	if(gdcl::file_exists(config_path)) {
		try {
			lua.safe_script_file(config_path);
		}
		catch(sol::error& e) {
			// failed to load the config. maybe there is a syntax error or
			// something.
			std::cout << "err0\n";
		}
	}
	else {
		// TODO default should probably be something better.
		lua[sol::create_if_nil]["gdcl"]["main_file"] = "../main.lua";
	}

	sol::optional<std::string> main_file = lua["gdcl"]["main_file"];
	if(! main_file.has_value() ||
	   ! gdcl::file_exists(gdcl::exe_path() + '/' + main_file.value())) {
		// no main file found.
		// TODO error out or somethin.
		std::cout << "err1\n";
	}

	/* LUA API

		-- INPT:

		(enum) inpt.button_state = { up, down }

		(type) inpt.event_button = { uint id, inpt.button_state state }
		(type) inpt.event_axis   = { uint id, float state }

		(enum) inpt.event_type = { button, axis }

		(type) inpt.event = {
			inpt.event.type type,
			inpt.event_button button,
			inpt.event_axis axis
		}

	*/

	// create inpt namespace:
	auto inpt = lua["inpt"].get_or_create<sol::table>();

	// create inpt::button_state enum:
	// inpt.new_enum("button_state", "up", inpt::button_state::up, "down",
	// 			  inpt::button_state::down);
	inpt[sol::create_if_nil]["button_state"]["up"]	 = inpt::button_state::up;
	inpt[sol::create_if_nil]["button_state"]["down"] = inpt::button_state::down;

	// create inpt::event_button type:
	auto inpt_event_button =
		inpt.new_usertype<inpt::event_button>("event_button");
	inpt_event_button["id"] = &inpt::event_button::id;
	inpt_event_button["state"] = &inpt::event_button::state;

	// create inpt::event_axis type:
	auto inpt_event_axis = inpt.new_usertype<inpt::event_axis>("event_axis");
	inpt_event_axis["id"] = &inpt::event_axis::id;
	inpt_event_axis["value"] = &inpt::event_axis::value;

	inpt[sol::create_if_nil]["event_type"]["button"] =
		inpt::event::type::button;
	inpt[sol::create_if_nil]["event_type"]["axis"] = inpt::event::type::axis;

	// create inpt::event type:
	auto inpt_event		 = inpt.new_usertype<inpt::event>("event");
	inpt_event["type"]	 = &inpt::event::type;
	inpt_event["button"] = &inpt::event::button;
	inpt_event["axis"]	 = &inpt::event::axis;

	// load the main file. this should initialize things and assign functions
	// for running.
	try {
		// TODO support absolute paths
		lua.safe_script_file(gdcl::exe_path() + '/' + main_file.value());
	}
	catch(sol::error& e) {
		// failed to load the main file. (probably a syntax error.)
		std::cout << "err2\n";
		return -1;
	}

	// get function like init, kill, and loop from main file if they are
	// defined.
	sol::optional<sol::function> optional_func_init	 = lua["init"];
	sol::optional<sol::function> optional_func_kill	 = lua["kill"];
	sol::optional<sol::function> optional_func_loop	 = lua["loop"];
	sol::optional<sol::function> optional_func_input = lua["input"];

	// TODO implement in-between layer to check if there is an error in the
	// function during runtime.
	if(optional_func_init.has_value()) {
		func_init = optional_func_init.value();
	}

	if(optional_func_kill.has_value()) {
		func_kill = optional_func_kill.value();
	}

	if(optional_func_loop.has_value()) {
		func_loop = optional_func_loop.value();
	}

	if(optional_func_input.has_value()) {
		func_input = optional_func_input.value();
	}

	return 0;
}

static const std::string to_string(sol::object&);
static const std::string table_to_string(const sol::table&);

static const std::string to_string(const sol::table& table) {
	std::string out;
	for(auto pair : table) {
		out +=
			"'" + to_string(pair.first) + "': " + to_string(pair.second) + '\n';
	}

	return out;
}

static const std::string to_string(sol::object& o) {
	switch(o.get_type()) {
		case sol::type::string:
			return o.as<std::string>();

		case sol::type::number:
			return std::to_string(o.as<double>());

		case sol::type::boolean:
			return std::to_string(o.as<bool>());

		case sol::type::table:
			return to_string(o.as<const sol::table&>());

		case sol::type::lua_nil:
			return "nil";

		default:
			return std::string();
	}
}

const std::string execute(const std::string& script) {
	sol::object obj;

	try {
		obj = lua.safe_script("return " + script);
	}
	catch(sol::error e) {
		// TODO fix this because I hate it. also, the error still prints in the
		// console it is running in which is bad.
		try {
			obj = lua.safe_script(script);
		}
		catch(sol::error e2) {
			throw std::runtime_error(e2.what());
		}
	}

	return to_string(obj);
}

} // namespace script
} // namespace gdcl