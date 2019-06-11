#include "harpoon/execution/execution_unit.hh"

namespace harpoon {
namespace execution {

execution_unit::~execution_unit() {}

void execution_unit::set_clock(const harpoon::clock::clock_ptr &clock) {
	replace_component(_clock, clock);
	_clock = clock;
}

} // namespace execution
} // namespace harpoon
