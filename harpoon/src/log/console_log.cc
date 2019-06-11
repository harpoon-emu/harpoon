#include "harpoon/log/console_log.hh"

#include "harpoon/log/message.hh"

#include <iostream>

namespace harpoon {
namespace log {

console_log::~console_log() {}

void console_log::out(const message &message) {

	std::lock_guard<std::mutex> lk(_mutex);

	if (_display_component) {
		std::cout << "[" << message.get_component() << "] ";
	}
	if (_display_file && _display_line) {
		std::cout << message.get_file() << ":" << message.get_line() << " ";
	} else if (_display_file) {
		std::cout << message.get_file() << " ";
	}
	if (_display_function) {
		std::cout << "@" << message.get_function() << "(): ";
	}
	std::cout << message.get_text() << std::endl;
}

} // namespace log
} // namespace harpoon
