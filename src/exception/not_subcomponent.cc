#include "harpoon/exception/not_subcomponent.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace exception {

not_subcomponent::not_subcomponent(const std::string &component,
                                   const harpoon::hardware_component_weak_ptr &child,
                                   const std::string &file, int line, const std::string &function)
    : hardware_component_exception(component, "", file, line, function), _child(child) {
	std::stringstream stream;
	stream << "Component [" << _child->get_name() << "] is not a subcomponent.";
	set_what(stream.str());
}

not_subcomponent::~not_subcomponent() {}

} // namespace exception
} // namespace harpoon
