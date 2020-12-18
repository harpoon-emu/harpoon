#ifndef HARPOON_CLOCK_CYCLE_HH
#define HARPOON_CLOCK_CYCLE_HH

#include "harpoon/harpoon.hh"

#include <atomic>
#include <iostream>

namespace harpoon {
namespace clock {

using tick_t = std::uint64_t;
using phase_t = std::uint64_t;

struct cycle {
	tick_t tick;
	phase_t phase;
};

static inline std::ostream &operator<<(std::ostream &stream, const cycle &c) {
	std::ostream out(stream.rdbuf());
	out << "[T: " << c.tick << ", P: " << c.phase << "]";
	return stream;
}

} // namespace clock
} // namespace harpoon

#endif
