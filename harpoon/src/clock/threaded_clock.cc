#include "harpoon/clock/threaded_clock.hh"

namespace harpoon {
namespace clock {

threaded_clock::~threaded_clock() {}

void threaded_clock::prepare() {
	_missed_ticks = 0;
}

void threaded_clock::boot() {
	clock::boot();

	_thread.reset(new std::thread([this] {
		while (is_running()) {
			;
		}
	}));
}

void threaded_clock::shutdown() {
	if (_thread) {
		_thread->join();
		_thread.reset();
	}

	clock::shutdown();
}

void threaded_clock::log_state(log::message::Level level) const {
	clock::log_state(level);
}

} // namespace clock
} // namespace harpoon
