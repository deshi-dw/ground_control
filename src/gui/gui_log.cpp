#include "gui/gui_log.hpp"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

namespace gui {

void log::print(const std::string& val) {
	items.push_back({val, {0.65f, 0.65f, 0.65f}});
	scroll_to_bottom = true;
}

void log::warn(const std::string& val) {
	items.push_back({"[warn] " + val, {1.0f, 1.0f, 0.5f}});
	scroll_to_bottom = true;
}
void log::error(const std::string& val) {
	items.push_back({"[error] " + val, {1.0f, 0.5f, 0.5f}});
	scroll_to_bottom = true;
}

void log::draw() {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

	ImGui::Begin("console", &is_open);

	// scrollable log section:
	ImGui::BeginChild("ScrollingRegion",
					  ImVec2(0, -(ImGui::GetStyle().ItemSpacing.y +
								  ImGui::GetFrameHeightWithSpacing())),
					  false, ImGuiWindowFlags_HorizontalScrollbar);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
	for(int i = 0; i < items.size(); i++) {
		ImGui::PushStyleColor(
			ImGuiCol_Text,
			ImVec4(items[i].color.r, items[i].color.g, items[i].color.b, 1.0f));

		ImGui::TextUnformatted(items[i].text.c_str());
		ImGui::PopStyleColor();
	}

	if(scroll_to_bottom) {
		ImGui::SetScrollHereY(1.0f);
		scroll_to_bottom = false;
	}

	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	int flags = ImGuiInputTextFlags_EnterReturnsTrue |
				ImGuiInputTextFlags_CallbackHistory;
	auto callback = [](ImGuiInputTextCallbackData* data) -> int {
		gui::log* _this = (gui::log*) data->UserData;
		// handle command history.
        // TODO preserve the command being currently typed.
		if(data->EventFlag == ImGuiInputTextFlags_CallbackHistory) {
			if(data->EventKey == ImGuiKey_UpArrow) {
				_this->history_index =
					_this->history_index <= 0 ? 0 : _this->history_index - 1;
			}
			else if(data->EventKey == ImGuiKey_DownArrow) {
				_this->history_index =
					_this->history_index >= _this->history.size() - 1
						? _this->history.size() - 1
						: _this->history_index + 1;
			}

            _this->input = _this->history[_this->history_index];
		}

		return 0;
	};
	if(ImGui::InputText("##input", &input, flags, callback, (void*) this)) {
        // TODO evaluate input:
		print(input);
		history.push_back(input);
		history_index = history.size() - 1;

		// refocus input after execution.
		ImGui::SetItemDefaultFocus();
		ImGui::SetKeyboardFocusHere(-1);

		if(on_input) {
			on_input(input);
		}

		input.clear();

		scroll_to_bottom = true;
	}

	// scroll to the bottom.
	if(scroll_to_bottom) {
		ImGui::SetScrollHereY(1.0f);
	}

	ImGui::End();
}

} // namespace gui