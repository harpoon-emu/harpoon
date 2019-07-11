#include "harpoon/memory/serializer/exception/bad_block_range.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace memory {
namespace serializer {
namespace exception {

bad_block_range::bad_block_range(const address_range &block_range, const address_range &range,
                                 const std::string &file, int line, const std::string &function)
    : harpoon::exception::harpoon_exception("", file, line, function) {
	std::stringstream stream;
	stream << "Bad memory block range. Block range: " << block_range;
	stream << ", Allowed: " << range;

	set_what(stream.str());
}

bad_block_range::~bad_block_range() {}

} // namespace exception
} // namespace serializer
} // namespace memory
} // namespace harpoon
