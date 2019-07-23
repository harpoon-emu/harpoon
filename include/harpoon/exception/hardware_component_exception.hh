#ifndef HARPOON_EXCEPTION_HARDWARE_COMPONENT_EXCEPTION_HH
#define HARPOON_EXCEPTION_HARDWARE_COMPONENT_EXCEPTION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/harpoon_exception.hh"

namespace harpoon {
namespace exception {

class hardware_component_exception : public harpoon_exception {
public:
	hardware_component_exception(const std::string &component, const std::string &what = {},
	                             const std::string &file = {}, int line = {},
	                             const std::string &function = {})
	    : harpoon_exception(what, file, line, function), _component(component) {}

	hardware_component_exception(const hardware_component_exception &) = default;
	hardware_component_exception &operator=(const hardware_component_exception &) = default;

	const std::string &get_component() const {
		return _component;
	}

	virtual ~hardware_component_exception();

private:
	std::string _component{};
};

#define COMPONENT_EXCEPTION(EXCEPTION, ...) \
	HARPOON_EXCEPTION(EXCEPTION, this->get_name(), __VA_ARGS__)

#define COMPONENT_EXCEPTION0(EXCEPTION) HARPOON_EXCEPTION(EXCEPTION, this->get_name())

} // namespace exception
} // namespace harpoon

#endif
