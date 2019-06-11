#include "log_window.hh"

namespace commodore {
namespace ui {

log_window::log_window(QWidget *parent) : QTextEdit(parent) {
	setAcceptRichText(false);
	setReadOnly(true);
}

void log_window::log_message(const harpoon::log::message &message) {
	if (message.get_level() == harpoon::log::message::Level::ERROR) {
		setTextColor({255, 0, 0});
	} else {
		setTextColor({0, 0, 0});
	}
	append((message.get_component() + ": " + message.get_text()).c_str());
}

} // namespace ui
} // namespace commodore
