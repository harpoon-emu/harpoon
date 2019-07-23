#include "harpoon/exception/harpoon_exception.hh"

namespace harpoon {
namespace exception {

harpoon_exception::~harpoon_exception() {}

const char *harpoon_exception::what() const noexcept(true) {
	(void)_line;
	return _what.c_str();
}

} // namespace exception
} // namespace harpoon
