#ifndef GUI_LOG_H
#define GUI_LOG_H

#include <string>
#include <vector>
#include <functional>

namespace gui {

struct log {
	private:
	struct item {
		std::string text;
		// TODO make color a uint8_t and use it as a color id to save memory.
		struct {
			float r;
			float g;
			float b;
		} color;
	};

	bool scroll_to_bottom = false;
	bool is_open;

	public:
	int						 history_index;
	std::vector<std::string> history;
	std::vector<item>		 items;

	std::string input;

	std::function<void(const std::string&)> on_input;

	void print(const std::string&);
	void warn(const std::string&);
	void error(const std::string&);

	void draw();
};

} // namespace gui

#endif
