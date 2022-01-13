#include "gui/gui.hpp"
#include "gui/gui_log.hpp"

#include "gdcl/rs/rs.h"

#include "imgui.h"

int main(int argc, char** argv) {
	

	exit(0);

	gdcl::rs::rs().run(argv[1]);
	exit(0);

	gui::gui ui("help", 1280, 720);
	gui::log log;

	bool is_open;

	for(int i = 0; i < std::stoi(argv[1]); i++) {
		log.print("test print");
		log.print("help");
		log.warn("hello, world.");
		log.error("a fucking error. ok.");
		log.print("");
	}

	ui.run([&] {
		// ImGui::ShowDemoWindow(&is_open);
		log.draw();
	});

	return 0;
}