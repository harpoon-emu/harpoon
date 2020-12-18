#ifndef HARPOON_CLOCK_CYCLE_HH
#define HARPOON_CLOCK_CYCLE_HH

#include "harpoon/harpoon.hh"

#include <atomic>

namespace harpoon {
namespace clock {

using tick_t = std::uint64_t;
using phase_t = std::uint64_t;

struct cycle {
	tick_t tick;
	phase_t phase;
};

} // namespace clock
} // namespace harpoon

#endif
