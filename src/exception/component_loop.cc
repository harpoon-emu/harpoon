#include "harpoon/exception/component_loop.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace exception {

component_loop::component_loop(const std::string &component,
                               const harpoon::hardware_component_weak_ptr &child,
                               const std::string &file, int line, const std::string &function)
    : hardware_component_exception(component, "", file, line, function), _child(child) {
	std::stringstream stream;
	stream << "Detected component loop. Subcomponent: [" << _child->get_name() << "].";
	set_what(stream.str());
}

component_loop::~component_loop() {}

} // namespace exception
} // namespace harpoon
