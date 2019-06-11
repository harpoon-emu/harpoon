#ifndef HARPOON_CLOCK_TICK_HH
#define HARPOON_CLOCK_TICK_HH

#include "harpoon/harpoon.hh"

#include <atomic>

namespace harpoon {
namespace clock {

using tick = std::uint_fast64_t;
using atomic_tick = std::atomic_uint_fast64_t;

} // namespace clock
} // namespace harpoon

#endif
