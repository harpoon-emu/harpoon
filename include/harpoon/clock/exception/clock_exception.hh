#ifndef HARPOON_CLOCK_EXCEPTION_CLOCK_EXCEPTION_HH
#define HARPOON_CLOCK_EXCEPTION_CLOCK_EXCEPTION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"

namespace harpoon {
namespace clock {
namespace exception {

class clock_exception : public harpoon::exception::hardware_component_exception {
public:
	using harpoon::exception::hardware_component_exception::hardware_component_exception;

	clock_exception(const clock_exception &) = default;
	clock_exception &operator=(const clock_exception &) = default;

	virtual ~clock_exception();
};

} // namespace exception
} // namespace clock
} // namespace harpoon

#endif
