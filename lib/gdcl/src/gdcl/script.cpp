#include "gdcl/script.h"

#include "gdcl/util.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include <lua5.3/lua.hpp>

namespace gdcl {
namespace script {

static lua_State* state;

// TODO redefine print function to redirect it.

static const std::string script_error() {
	const std::string err(lua_tostring(state, -1));
	lua_pop(state, 1);
	return err;
}

static const std::string script_to_string(int idx);

static const std::string script_table_to_string(int idx) {
	std::string str = "{ ";

	// push table value to -2 and nil to -1.
	lua_pushvalue(state, idx);
	lua_pushnil(state);

	// loop through all items in the table.
	while(lua_next(state, -2)) {
		// copy key value at index -2, to the top of the stack.
		lua_pushvalue(state, -2);

		// convert key value to string.
		std::string key	  = lua_tostring(state, -1);
		std::string value = script_to_string(-2);

		if(str.size() > 3) {
			str += ", ";
		}
		str += key + ": " + value;

		// pop the copy of the key and value from the stack.
		lua_pop(state, 2);
	}

	// pop table from the stack.
	lua_pop(state, 1);

	str += " }";
	return str;
}

static const std::string script_to_string(int idx) {
	switch(lua_type(state, idx)) {
		case LUA_TNUMBER: {
			const char* val = lua_tostring(state, idx);
			if(val == nullptr) {
				return "null";
			}
			return val;
		}
		case LUA_TSTRING: {
			const char* val = lua_tostring(state, idx);
			if(val == nullptr) {
				return "null";
			}
			return val;
		}
		case LUA_TBOOLEAN:
			return lua_toboolean(state, idx) == 1 ? "true" : "false";
		case LUA_TFUNCTION:
			return "function";
		case LUA_TTABLE:
			return script_table_to_string(idx);
		default:
			return "unknown";
	}
}

int load(const std::string& config_path) {
	// create a new lua state and open standard lua libraries.
	state = luaL_newstate();
	luaL_openlibs(state);

	// Load globals:
	lua_pushinteger(state, static_cast<int>(inpt::event::type::button));
	lua_setglobal(state, "EVENT_BUTTON");
	lua_pushinteger(state, static_cast<int>(inpt::event::type::axis));
	lua_setglobal(state, "EVENT_AXIS");

	lua_pushinteger(state, static_cast<int>(inpt::button_state::none));
	lua_setglobal(state, "BUTTON_NONE");
	lua_pushinteger(state, static_cast<int>(inpt::button_state::down));
	lua_setglobal(state, "BUTTON_DOWN");
	lua_pushinteger(state, static_cast<int>(inpt::button_state::up));
	lua_setglobal(state, "BUTTON_UP");
	lua_pushinteger(state, static_cast<int>(inpt::button_state::held));
	lua_setglobal(state, "BUTTON_HELD");

	// load config file if it exists or load a default config if it does not.
	if(! gdcl::file_exists(config_path)) {
		luaL_dostring(state, "gdcl={}; gdcl.config={main_file=\"main.lua\";}");
	}
	else {
		if(luaL_dofile(state, config_path.c_str()) != LUA_OK) {
			throw error("failed to do config file: " + script_error());
		}
	}

	// get the config from the lua state.
	lua_getglobal(state, "gdcl");
	if(! lua_istable(state, -1)) {
		throw error("failed to get config value: "
					"gdcl is not a table.");
	}

	// get the config field.
	lua_getfield(state, -1, "config");
	if(! lua_istable(state, -1)) {
		throw error("failed to get config value: "
					"gdcl.config is not a table.");
	}

	// get the main_file field of the config table.
	lua_getfield(state, -1, "main_file");

	const std::string& main_file = lua_tostring(state, -1);

	// TODO determine if the main_file is a relative or absolute path.

	// check if main_file exists.
	std::string full_path = gdcl::exe_path() + "/" + main_file;
	if(! gdcl::file_exists(full_path)) {
		throw(error("failed to get config value: "
					"main_file path doesn't exist. path = " +
					full_path));
	}

	// try to execute main_file.
	if(luaL_dofile(state, full_path.c_str()) != LUA_OK) {
		throw error("lua error: " + script_error());
	}

	return 0;
}

int close() {
	lua_close(state);

	return 0;
}

int init() {
	// get init function and check that it is a function.
	lua_getglobal(state, "gdcl_init");
	if(! lua_isfunction(state, -1)) {
		return 0;
	}

	// call function.
	if(lua_pcall(state, 0, 0, 0) != LUA_OK) {
		throw error("lua error: " + script_error());
	}

	return 0;
}

int kill() {
	// get init function and check that it is a function.
	lua_getglobal(state, "gdcl_kill");
	if(! lua_isfunction(state, -1)) {
		return 0;
	}

	// call function.
	if(lua_pcall(state, 0, 0, 0) != LUA_OK) {
		throw error("lua error: " + script_error());
	}

	return 0;
}

int loop() {
	// get init function and check that it is a function.
	lua_getglobal(state, "gdcl_loop");
	if(! lua_isfunction(state, -1)) {
		return 0;
	}

	// call function.
	if(lua_pcall(state, 0, 0, 0) != LUA_OK) {
		throw error("lua error: " + script_error());
	}

	return 0;
}

int input(inpt::dev& dev, inpt::event e) {
	// get input function and check that it is a function.
	lua_getglobal(state, "gdcl_input");
	if(! lua_isfunction(state, -1)) {
		return 0;
	}

	// CREATE DEV TABLE AS ARGUMENT:
	lua_newtable(state);

	// set id:
	lua_pushstring(state, "id");
	lua_pushinteger(state, dev.id);
	lua_settable(state, -3);

	// set name:
	lua_pushstring(state, "name");
	lua_pushstring(state, dev.name.c_str());
	lua_settable(state, -3);

	// set vendor_id:
	lua_pushstring(state, "vendor_id");
	lua_pushinteger(state, dev.vendor_id);
	lua_settable(state, -3);

	// set product_id:
	lua_pushstring(state, "product_id");
	lua_pushinteger(state, dev.product_id);
	lua_settable(state, -3);

	// set axis array:
	lua_pushstring(state, "axis");
	lua_newtable(state);

	for(int i = 0; i < dev.axis.size(); i++) {
		lua_pushnumber(state, dev.axis[i]);
		lua_rawseti(state, -2, i + 1);
	}

	lua_settable(state, -3);

	// set button array:
	lua_pushstring(state, "buttons");
	lua_newtable(state);

	for(int i = 0; i < dev.axis.size(); i++) {
		lua_pushinteger(state, static_cast<int>(dev.buttons[i]));
		lua_rawseti(state, -2, i + 1);
	}

	lua_settable(state, -3);

	// CREATE EVENT TABLE AS ARGUMENT:
	lua_newtable(state);

	// set type:
	lua_pushstring(state, "type");
	lua_pushinteger(state, static_cast<int>(e.type));
	lua_settable(state, -3);

	// set id:
	lua_pushstring(state, "id");
	lua_pushinteger(state, e.id);
	lua_settable(state, -3);
	
	if(e.type == inpt::event::type::button) {
		// set state:
		lua_pushstring(state, "state");
		lua_pushinteger(state, static_cast<int>(e.state));
		lua_settable(state, -3);
	}
	else if(e.type == inpt::event::type::axis) {
		// set axis:
		lua_pushstring(state, "value");
		lua_pushnumber(state, e.value);
		lua_settable(state, -3);
	}

	// std::cout << script_to_string(-1) << '\n';

	// call function.
	if(lua_pcall(state, 2, 0, 0) != LUA_OK) {
		throw error("lua error: " + script_error());
	}

	return 0;
}

const std::string execute(const std::string& script) {
	// attempt to run the script.
	lua_pushnil(state);
	if(luaL_dostring(state, ("return " + script).c_str()) != LUA_OK) {
		// pop error off the stack just in case I guess.
		std::string err1 = script_error();

		if(luaL_dostring(state, script.c_str()) != LUA_OK) {
			script_error();
			throw(error("lua error: " + err1));
		}
	}
	else {
		// running the script worked and it returned a value to print.

		// if there is only one return value, just return that value.
		if(lua_type(state, -2) == LUA_TNIL) {
			return script_to_string(-1);
		}

		std::string ret;

		// if the script returned multiple values, get and return them all.
		while(lua_type(state, -1) != LUA_TNIL) {
			ret += script_to_string(-1) + ", ";
			lua_pop(state, 1);
		}

		// pop nil value.
		lua_pop(state, 1);

		return ret;
	}

	return std::string();
}

} // namespace script
} // namespace gdcl