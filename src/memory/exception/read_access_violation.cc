#include "harpoon/memory/exception/read_access_violation.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace memory {
namespace exception {

read_access_violation::read_access_violation(const std::string &component,
                                             harpoon::memory::address address,
                                             const std::string &file, int line,
                                             const std::string &function)
    : access_violation(component, address, file, line, function) {
	std::stringstream stream;
	stream << "Memory read access violation at 0x" << std::setfill('0')
	       << std::setw(sizeof(address) * 2) << std::hex << address;
	set_what(stream.str());
}

read_access_violation::~read_access_violation() {}

} // namespace exception
} // namespace memory
} // namespace harpoon
