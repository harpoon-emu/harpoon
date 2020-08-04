#include "harpoon/exception/wrong_state.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace exception {

wrong_state::wrong_state(const std::string &component,
                         const harpoon::hardware_component::state &actual,
                         const harpoon::hardware_component::state &expected,
                         const std::string &file, int line, const std::string &function)
    : hardware_component_exception(component, "", file, line, function) {
	std::stringstream stream;
	stream << "Component in wrong state. Actual: " << actual << ", expected: " << expected;
	set_what(stream.str());
}

wrong_state::~wrong_state() {}

} // namespace exception
} // namespace harpoon
