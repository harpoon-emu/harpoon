#include "harpoon/memory/exception/access_violation.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace memory {
namespace exception {

access_violation::access_violation(const std::string &component, harpoon::memory::address address,
                                   const std::string &file, int line, const std::string &function)
    : memory_exception(component, "", file, line, function), _address(address) {
	std::stringstream stream;
	stream << "Memory access violation at 0x" << std::setfill('0') << std::setw(sizeof(address) * 2)
	       << std::hex << address;
	set_what(stream.str());
}

access_violation::~access_violation() {}

} // namespace exception
} // namespace memory
} // namespace harpoon
