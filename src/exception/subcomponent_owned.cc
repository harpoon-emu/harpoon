#include "harpoon/exception/subcomponent_owned.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace exception {

subcomponent_owned::subcomponent_owned(const std::string &component,
                                       const harpoon::hardware_component_weak_ptr &child,
                                       const std::string &file, int line,
                                       const std::string &function)
    : hardware_component_exception(component, "", file, line, function), _child(child) {
	std::stringstream stream;
	stream << "Component [" << _child->get_name() << "] is already subcomponent of component ["
	       << _child->get_parent_component()->get_name() << "].";
	set_what(stream.str());
}

subcomponent_owned::~subcomponent_owned() {}

} // namespace exception
} // namespace harpoon
