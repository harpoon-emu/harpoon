#ifndef HARPOON_EXECUTION_BREAKPOINT_HH
#define HARPOON_EXECUTION_BREAKPOINT_HH

#include "harpoon/harpoon.hh"

#include <functional>

namespace harpoon {
namespace execution {

class processing_unit;

class breakpoint {
public:
	using condition = std::function<bool(processing_unit *)>;
	using action = std::function<void(processing_unit *)>;

	breakpoint(const condition &condition, const action &action)
	    : _condition(condition), _action(action) {}
	breakpoint(const breakpoint &) = default;
	breakpoint &operator=(const breakpoint &) = default;

	bool check_condition(processing_unit *processing_unit) const {
		return _condition(processing_unit);
	}

	void do_action(processing_unit *processing_unit) const {
		_action(processing_unit);
	}

private:
	condition _condition{};
	action _action{};
};

} // namespace execution
} // namespace harpoon

#endif
