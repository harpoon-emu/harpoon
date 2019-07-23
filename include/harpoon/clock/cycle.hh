#ifndef HARPOON_CLOCK_CYCLE_HH
#define HARPOON_CLOCK_CYCLE_HH

#include "harpoon/harpoon.hh"

#include <atomic>

namespace harpoon {
namespace clock {

struct cycle {
	std::uint64_t tick;
	std::uint64_t phase;
};

} // namespace clock
} // namespace harpoon

#endif
