#ifndef HARPOON_CLOCK_GENERATOR_HH
#define HARPOON_CLOCK_GENERATOR_HH

#include "harpoon/harpoon.hh"

#include <atomic>

namespace harpoon {
namespace clock {
namespace generator {

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

	std::uint64_t get_tick() const {
		return _tick;
	}

	void wait_for_tick(std::uint64_t tick) {
		while (_tick.load() < tick);
	}

	void wait_tick(std::uint64_t tick_count = 1) {
		wait_for_tick(_tick.load() + tick_count);
	}

	void tick() {
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
	void set_tick(std::uint64_t tick) {
		_tick = tick;
	}

	std::atomic_uint_fast64_t& get_atomic_tick() {
		return _tick;
	}

	const std::atomic_uint_fast64_t& get_atomic_tick() const {
		return _tick;
	}

private:
	std::uint32_t _frequency{};
	std::atomic_uint_fast64_t _tick{};
	std::atomic_bool _running{};
};

}
}
}

#endif