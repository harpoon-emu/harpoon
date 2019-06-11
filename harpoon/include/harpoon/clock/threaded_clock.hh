#ifndef HARPOON_CLOCK_THREADED_CLOCK_HH
#define HARPOON_CLOCK_THREADED_CLOCK_HH

#include "harpoon/harpoon.hh"

#include "harpoon/clock/clock.hh"

#include <atomic>
#include <thread>

namespace harpoon {
namespace clock {

template<typename TrivialClock>
class threaded_clock : public clock {
public:
	using clock::clock;
	threaded_clock(const threaded_clock &) = delete;
	threaded_clock &operator=(const threaded_clock &) = delete;

	virtual ~threaded_clock() override {}

	virtual void prepare() override {
		_waits = 0;
		_no_waits = 0;
		_missed_ticks = 0;
	}

	virtual void boot() override {
		clock::boot();

		_start = TrivialClock::now();

		_thread.reset(new std::thread([this] {
			tick current = 0;
			while (is_running()) {
				current = wait_for_tick(current + 1);
			}
		}));
	}

	virtual void shutdown() override {
		clock::shutdown();

		if (_thread) {
			_thread->join();
			_thread.reset();
		}
	}

	virtual tick get_tick() const override {
		auto dur = TrivialClock::now() - _start;
		std::uint32_t tick_ns = 1000000000 / get_frequency();
		std::uint64_t elapsed = static_cast<std::uint64_t>(
		    std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count());

		return elapsed / tick_ns;
	}

	virtual tick wait_for_tick(tick tick) override {

		std::uint32_t tick_ns = 1000000000 / get_frequency();
		typename TrivialClock::time_point tick_time
		    = _start + std::chrono::nanoseconds(tick_ns * tick);
		auto now = TrivialClock::now();

		if (now < tick_time) {
			std::this_thread::sleep_for(tick_time - now);
			_waits++;
		} else {
			_missed_ticks
			    += static_cast<std::uint64_t>(
			           std::chrono::duration_cast<std::chrono::nanoseconds>(now - tick_time)
			               .count())
			       / tick_ns;
			_no_waits++;
		}
		return get_tick();
	}

	virtual tick wait_tick(std::uint_fast64_t tick_count = 1) override {
		return wait_for_tick(get_tick() + tick_count);
	}

	virtual void log_state(log::message::Level level) const override {
		clock::log_state(level);

		tick t = get_tick();

		log(component_log(level) << "Tick: " << t);
		log(component_log(level) << "Waits / no-Waits: " << _waits << " / " << _no_waits);
		log(component_log(level) << "Missed ticks (total / avg): " << _missed_ticks << " / "
		                         << (_no_waits != 0 ? _missed_ticks / _no_waits : 0));
	}

private:
	std::unique_ptr<std::thread> _thread{};
	typename TrivialClock::time_point _start{};
	std::atomic_uint_fast64_t _waits{};
	std::atomic_uint_fast64_t _no_waits{};
	std::atomic_uint_fast64_t _missed_ticks{};
};

template<typename TrivialClock>
using threaded_clock_ptr = std::shared_ptr<threaded_clock<TrivialClock>>;

template<typename TrivialClock>
using threaded_clock_weak_ptr = std::weak_ptr<threaded_clock<TrivialClock>>;

template<typename TrivialClock, typename... Args>
threaded_clock_ptr<TrivialClock> make_threaded_clock(Args &&... args) {
	return std::make_shared<threaded_clock<TrivialClock>>(std::forward<Args>(args)...);
}

} // namespace clock
} // namespace harpoon

#endif
