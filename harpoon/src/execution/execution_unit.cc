#include "harpoon/execution/execution_unit.hh"

using namespace harpoon::execution;

execution_unit::~execution_unit() {}

void execution_unit::set_clock(const harpoon::clock::clock_ptr& clock) {
	replace_component(_clock, clock);
	_clock = clock;
}
