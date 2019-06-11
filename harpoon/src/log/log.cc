#include "harpoon/log/log.hh"

namespace harpoon {
namespace log {

log::~log() {}

void log::out(const std::ostream &stream) {
	message::streambuf *sbuf = reinterpret_cast<message::streambuf *>(stream.rdbuf());
	out(sbuf->get_message());
}

} // namespace log
} // namespace harpoon
