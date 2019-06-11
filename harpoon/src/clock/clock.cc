#include "harpoon/clock/clock.hh"

using namespace harpoon::clock;

namespace harpoon {
namespace clock {

clock::~clock() {}

void clock::boot() {
	hardware_component::boot();
}

void clock::shutdown() {
	hardware_component::shutdown();
}

void clock::log_state(log::message::Level level) const {
	hardware_component::log_state(level);
}

} // namespace clock
} // namespace harpoon
