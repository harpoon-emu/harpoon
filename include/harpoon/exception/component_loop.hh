#ifndef HARPOON_EXCEPTION_COMPONENT_LOOP_HH
#define HARPOON_EXCEPTION_COMPONENT_LOOP_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace exception {

class component_loop : public hardware_component_exception {
public:
	component_loop(const std::string &component, const hardware_component_weak_ptr &child,
	               const std::string &file = {}, int line = {}, const std::string &function = {});

	component_loop(const component_loop &) = default;
	component_loop &operator=(const component_loop &) = default;

	virtual ~component_loop();

private:
	hardware_component_ptr _child{};
};

} // namespace exception
} // namespace harpoon

#endif
