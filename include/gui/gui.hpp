#ifndef GUI_H
#define GUI_H

#include <string>
#include <functional>

namespace gui {

struct gui {
	bool redraw = true;

	gui(const std::string& title, int width = 1280, int height = 720);
	~gui();

    int run(std::function<void()> routine, long draw_interval = 20);
};

} // namespace ui

#endif