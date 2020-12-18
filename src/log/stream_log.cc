#include "harpoon/log/stream_log.hh"

#include "harpoon/log/message.hh"

#include <iostream>

namespace harpoon {
namespace log {

stream_log::~stream_log() {}

void stream_log::out(const message &message) {

	std::lock_guard<std::mutex> lk(_mutex);

	if (_display_component) {
		_stream << "[" << message.get_component() << "] ";
	}
	if (_display_file && _display_line) {
		_stream << message.get_file() << ":" << message.get_line() << " ";
	} else if (_display_file) {
		_stream << message.get_file() << " ";
	}
	if (_display_function) {
		_stream << "@" << message.get_function() << "(): ";
	}
	_stream << message.get_text() << std::endl;
}

} // namespace log
} // namespace harpoon
