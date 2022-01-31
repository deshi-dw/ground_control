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

	bool is_open;
	bool is_script_init;

	gdcl::inpt::on_axis = [&](gdcl::inpt::dev& dev, int id, float value) {
		log.print("inpt dev[" + std::to_string(dev.id) + "], axis " +
				  std::to_string(id) + " : " + std::to_string(value));
	};

	gdcl::inpt::on_button = [&](gdcl::inpt::dev& dev, int id,
								gdcl::inpt::button_state state) {
		log.print("inpt dev[" + std::to_string(dev.id) + "], btn " +
				  std::to_string(id) + " : " +
				  std::to_string(static_cast<int>(state)));
	};

	gdcl::inpt::on_input = [&](gdcl::inpt::dev& dev, gdcl::inpt::event e) {
		if(is_script_init && gdcl::script::func_input) {
			gdcl::script::func_input(e);
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
			log.print(gdcl::script::execute(str));
		}
		catch(std::runtime_error e) {
			log.error(e.what());
		}
	};

	gdcl::timer test_timer;

	// initialize script world.
	// TODO this is all temp stuff anyways but this should go somewhere else and
	//      have a gui element that will trigger init and kill in the script.
	gdcl::script::func_init();
	is_script_init = true;

	ui.run([&] {
		// ImGui::ShowDemoWindow(&is_open);
		gdcl::inpt::poll();
		gdcl::script::func_loop();

		if(ui.redraw) {
			log.draw();
		}

		test_timer.call(1000, [&] {
			log.print("time: " + std::to_string(gdcl::time()));
		});
	});

	gdcl::script::func_kill();
	gdcl::inpt::deinit();

	return 0;
}