#ifndef HARPOON_EXCEPTION_NOT_SUBCOMPONENT_HH
#define HARPOON_EXCEPTION_NOT_SUBCOMPONENT_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/hardware_component_exception.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace exception {

class not_subcomponent : public hardware_component_exception {
public:
	not_subcomponent(const std::string &component, const hardware_component_weak_ptr &child,
	                 const std::string &file = {}, int line = {}, const std::string &function = {});

	not_subcomponent(const not_subcomponent &) = default;
	not_subcomponent &operator=(const not_subcomponent &) = default;

	virtual ~not_subcomponent();

private:
	hardware_component_ptr _child{};
};

} // namespace exception
} // namespace harpoon

#endif
