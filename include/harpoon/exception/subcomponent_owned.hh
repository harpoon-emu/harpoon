#ifndef HARPOON_EXCEPTION_SUBCOMPONENT_OWNED_HH
#define HARPOON_EXCEPTION_SUBCOMPONENT_OWNED_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace exception {

class subcomponent_owned : public hardware_component_exception {
public:
	subcomponent_owned(const std::string &component, const hardware_component_weak_ptr &child,
	                   const std::string &file = {}, int line = {},
	                   const std::string &function = {});

	subcomponent_owned(const subcomponent_owned &) = default;
	subcomponent_owned &operator=(const subcomponent_owned &) = default;

	virtual ~subcomponent_owned();

private:
	hardware_component_ptr _child{};
};

} // namespace exception
} // namespace harpoon

#endif
