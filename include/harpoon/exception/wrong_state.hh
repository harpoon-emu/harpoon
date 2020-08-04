#ifndef HARPOON_EXCEPTION_WRONG_STATE_HH
#define HARPOON_EXCEPTION_WRONG_STATE_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace exception {

class wrong_state : public hardware_component_exception {
public:
	wrong_state(const std::string &component, const hardware_component::state &actual,
	            const hardware_component::state &expected, const std::string &file = {},
	            int line = {}, const std::string &function = {});

	wrong_state(const wrong_state &) = default;
	wrong_state &operator=(const wrong_state &) = default;

	virtual ~wrong_state();
};

} // namespace exception
} // namespace harpoon

#endif
