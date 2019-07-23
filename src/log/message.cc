#include "harpoon/log/message.hh"

#include <sstream>

namespace harpoon {
namespace log {

message::~message() {}

std::string message::get_text() const {
	return _streambuf->str();
}

message::streambuf::~streambuf() {}

} // namespace log
} // namespace harpoon
