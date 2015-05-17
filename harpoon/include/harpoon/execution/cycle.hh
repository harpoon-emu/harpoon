#ifndef HARPOON_EXECUTION_CYCLE_HH
#define HARPOON_EXECUTION_CYCLE_HH

#include "harpoon/harpoon.hh"

#include <atomic>

namespace harpoon {
namespace execution {

using cycle = std::uint_fast64_t;
using atomic_cycle = std::atomic_uint_fast64_t;

}
}

#endif