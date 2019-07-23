#ifndef HARPOON_EXECUTION_EXCEPTION_EXECUTION_EXCEPTION_HH
#define HARPOON_EXECUTION_EXCEPTION_EXECUTION_EXCEPTION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"

namespace harpoon {
namespace execution {
namespace exception {

class execution_exception : public harpoon::exception::hardware_component_exception {
public:
	using harpoon::exception::hardware_component_exception::hardware_component_exception;

	execution_exception(const execution_exception &) = default;
	execution_exception &operator=(const execution_exception &) = default;

	virtual ~execution_exception();
};

} // namespace exception
} // namespace execution
} // namespace harpoon

#endif
