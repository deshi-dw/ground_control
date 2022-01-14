#include "gui/gui.hpp"
#include "gui/gui_log.hpp"

#include "gdcl/rs.h"
#include "gdcl/bot.h"

#include "imgui.h"

int main(int argc, char** argv) {
	gdcl::bot bot;

	// bot.connect("/dev/ttyUSB0", 9600, "test");
	// bot.print("Hello, world.");
	// bot.disconnect();

	// exit(0);

	// gdcl::rs::rs().run(argv[1]);
	// exit(0);

	gdcl::rs rs;

	gui::gui ui("help", 1280, 720);
	gui::log log;

	bool is_open;

	for(int i = 0; i < std::stoi(argv[1]); i++) {
		log.print("test print");
		log.print("help");
		log.warn("hello, world.");
		log.error("an error. ok.");
		log.print("");
	}

	log.on_input = [&](const std::string& str) {
		try {
			log.print(rs.run(str));
		}
		catch(std::runtime_error e) {
			log.error(e.what());
		}
	};

	ui.run([&] {
		// ImGui::ShowDemoWindow(&is_open);
		log.draw();
	});

	return 0;
}