#include "harpoon/clock/clock.hh"

#include <chrono>
#include <thread>

using namespace harpoon::clock;

namespace harpoon {
namespace clock {

clock::~clock() {}

void clock::boot() {
	hardware_component::boot();
	_cycle.tick = 0;
	_cycle.phase = 0;
}

void clock::shutdown() {
	hardware_component::shutdown();
}

void clock::log_state(log::message::Level level) const {
	hardware_component::log_state(level);
}

void clock::schedule(uint64_t delay, phase_t phase, step_handler &&fn) {
	_handlers.insert({{_cycle.tick + delay, phase}, fn});
}

void clock::step(hardware_component *) {

	auto start = std::chrono::high_resolution_clock::now();

	_cycle.phase = 0;

	auto i = std::begin(_handlers);
	while (i != std::end(_handlers) && i->first.first == _cycle.tick) {
		_cycle.phase = i->first.second;
		i->second(this);
		i = _handlers.erase(i);
	}

	if (_handlers.empty()) {
		throw std::runtime_error("DEAD CLOCK");
	}

	std::uint64_t ns = (std::begin(_handlers)->first.first - _cycle.tick) * 1000000000 / _frequency;
	std::this_thread::sleep_until<std::chrono::high_resolution_clock,
	                              std::chrono::high_resolution_clock::duration>(
	    start + std::chrono::nanoseconds(ns));

	_cycle.tick = std::begin(_handlers)->first.first;
}

} // namespace clock
} // namespace harpoon
