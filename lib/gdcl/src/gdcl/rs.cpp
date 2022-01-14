#include "gdcl/rs.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>

namespace gdcl {

// rs::rs() {
// }

// rs::~rs() {
// }

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

const std::string rs::run(const std::string& script) {
	// lua.script_file(script);
	sol::object obj;

	try {
		obj = lua.script("return " + script);
	}
	catch(sol::error e) {
		// TODO fix this because I hate it. also, the error still prints in the
		// console it is running in which is bad.
		try {
			obj = lua.script(script);
		}
		catch(sol::error e2) {
			throw std::runtime_error(e2.what());
		}
	}
	// sol::object d = lua["d"];

	// const std::string& somestr = d["somestr"];
	// std::cout << somestr + '\n';

	// if(! d.valid()) {
	// 	std::cout << "wha the fuck? \n";
	// }
	// else {
	// 	std::cout << to_string(d) + '\n';
	// }

	return to_string(obj);
}

} // namespace gdcl