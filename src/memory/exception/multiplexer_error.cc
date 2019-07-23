#include "harpoon/memory/exception/multiplexer_error.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace memory {
namespace exception {

multiplexer_error::multiplexer_error(const std::string &component, unsigned int mem_id,
                                     const std::string &file, int line, const std::string &function)
    : memory_exception(component, "", file, line, function) {
	std::stringstream stream;
	stream << "Memory multiplexer error: mem_id: 0x" << std::setfill('0')
	       << std::setw(sizeof(mem_id) * 2) << std::hex << mem_id;
	set_what(stream.str());
}

multiplexer_error::~multiplexer_error() {}

} // namespace exception
} // namespace memory
} // namespace harpoon
