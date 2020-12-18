#ifndef HARPOON_CLOCK_EXCEPTION_DEAD_CLOCK_HH
#define HARPOON_CLOCK_EXCEPTION_DEAD_CLOCK_HH

#include "harpoon/harpoon.hh"

#include "harpoon/clock/cycle.hh"
#include "harpoon/clock/exception/clock_exception.hh"

namespace harpoon {
namespace clock {
namespace exception {

class dead_clock : public clock_exception {
public:
	dead_clock(const std::string &component, cycle cycle, const std::string &file = {},
	           int line = {}, const std::string &function = {});

	dead_clock(const dead_clock &) = default;
	dead_clock &operator=(const dead_clock &) = default;

	virtual ~dead_clock();

	const cycle &get_cycle() const {
		return _cycle;
	}

private:
	cycle _cycle{};
};

} // namespace exception
} // namespace clock
} // namespace harpoon

#endif
