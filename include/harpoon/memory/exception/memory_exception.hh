#ifndef HARPOON_MEMORY_EXCEPTION_MEMORY_EXCEPTION_HH
#define HARPOON_MEMORY_EXCEPTION_MEMORY_EXCEPTION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"

namespace harpoon {
namespace memory {
namespace exception {

class memory_exception : public harpoon::exception::hardware_component_exception {
public:
	using harpoon::exception::hardware_component_exception::hardware_component_exception;

	memory_exception(const memory_exception &) = default;
	memory_exception &operator=(const memory_exception &) = default;

	virtual ~memory_exception();
};

} // namespace exception
} // namespace memory
} // namespace harpoon

#endif
