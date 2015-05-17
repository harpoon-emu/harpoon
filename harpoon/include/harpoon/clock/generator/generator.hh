#ifndef HARPOON_CLOCK_GENERATOR_HH
#define HARPOON_CLOCK_GENERATOR_HH

#include "harpoon/harpoon.hh"
#include "harpoon/clock/tick.hh"

#include <atomic>
#include <thread>

namespace harpoon {
namespace clock {
namespace generator {

using tick = harpoon::clock::tick;
using atomic_tick = harpoon::clock::atomic_tick;

class generator {
public:

	generator(std::uint32_t frequency = 1) : _frequency(frequency) {}
	generator(const generator&) = default;
	generator& operator=(const generator&) = default;

	virtual ~generator();

	void set_frequency(std::uint32_t frequency) {
		_frequency = frequency;
	}

	std::uint32_t get_frequency() const {
		return _frequency;
	}

	tick get_tick() const {
		return _tick;
	}

	virtual tick wait_for_tick(tick tick) {
		while (_tick < tick && is_running());
		return _tick;
	}

	virtual tick wait_tick(std::uint_fast64_t tick_count = 1) {
		return wait_for_tick(_tick.load() + tick_count);
	}

	void next_tick() {
		if (is_running()) {
			++_tick;
		}
	}

	bool is_running() const {
		return _running;
	}

	virtual void start();
	virtual void stop();

protected:
	void set_tick(tick tick) {
		_tick = tick;
	}

	atomic_tick& get_atomic_tick() {
		return _tick;
	}

	const atomic_tick& get_atomic_tick() const {
		return _tick;
	}

private:
	std::uint32_t _frequency{};
	atomic_tick _tick{};
	std::atomic_bool _running{};
};

using generator_ptr = std::shared_ptr<generator>;
using generator_weak_ptr = std::weak_ptr<generator>;

}
}
}

#endif