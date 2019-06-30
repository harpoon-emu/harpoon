#include "console_log.hh"

#include <iostream>

namespace c64 {
namespace cli {

console_log::~console_log() {}

void console_log::out(const harpoon::log::message &message) {
	std::cout << message.get_component() << ": " << message.get_text() << std::endl;
}

} // namespace cli
} // namespace c64
