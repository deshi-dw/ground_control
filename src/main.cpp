#include "gui/gui.hpp"
#include "gui/gui_log.hpp"

#include "gdcl/gdcl.h"

#include "imgui.h"

#include <string>

int main(int argc, char** argv) {
	gdcl::bot bot;

	// bot.connect(argv[1], 9600, "test");
	// bot.print("Hello, world.");
	// bot.disconnect();

	// exit(0);

	// gdcl::rs::rs().run(argv[1]);
	// exit(0);

	gdcl::script::load(gdcl::exe_path() + "/config.lua");

	gdcl::inpt::init();

	gui::gui ui("help", 1280, 720);
	gui::log log;

	bool is_script_init;

	gdcl::inpt::on_input = [&](gdcl::inpt::dev& dev, gdcl::inpt::event e) {
		if(is_script_init) {
			try {
				gdcl::script::input(dev, e);
			}
			catch(gdcl::script::error err) {
				log.error(err.what());
			}
		}
	};

	for(int i = 0; i < std::stoi(argv[1]); i++) {
		log.print("test print");
		log.print("help");
		log.warn("hello, world.");
		log.error("an error. ok.");
		log.print("");
	}

	log.on_input = [&](const std::string& str) {
		try {
			log.print("-> " + gdcl::script::execute(str));
		}
		catch(gdcl::script::error e) {
			log.error(e.what());
		}
	};

	gdcl::timer test_timer;
	gdcl::timer loop_timer;

	// initialize script world.
	// TODO this is all temp stuff anyways but this should go somewhere else and
	//      have a gui element that will trigger init and kill in the script.

	gdcl::time_start();
	try {
		gdcl::script::init();
	}
	catch(gdcl::script::error e) {
		log.error(e.what());
	}

	is_script_init = true;

	ui.run([&] {
		gdcl::inpt::poll();

		// call loop function every 20 ms.
		loop_timer.call(20, [&] {
			try {
				gdcl::script::loop();
			}
			catch(gdcl::script::error e) {
				log.error(e.what());
			}
		});

		if(ui.redraw) {
			log.draw();
		}

		test_timer.call(1000, [&] {
			log.print("time: " + std::to_string(gdcl::time()));
		});
	});

	try {
	gdcl::script::kill();
	}
	catch(gdcl::script::error e) {
		log.error(e.what());
	}

	gdcl::inpt::deinit();

	return 0;
}