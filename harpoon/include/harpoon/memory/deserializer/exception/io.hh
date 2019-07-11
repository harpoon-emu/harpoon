#ifndef HARPOON_MEMORY_DESERIALIZER_EXCEPTION_IO_HH
#define HARPOON_MEMORY_DESERIALIZER_EXCEPTION_IO_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/harpoon_exception.hh"

namespace harpoon {
namespace memory {
namespace deserializer {
namespace exception {

class io : public harpoon::exception::harpoon_exception {
public:
	io(const std::string &infile, const std::string &file = {}, int line = {},
	   const std::string &function = {});
	io(const io &) = default;
	io &operator=(const io &) = default;

	virtual ~io();
};

} // namespace exception
} // namespace deserializer
} // namespace memory
} // namespace harpoon

#endif
