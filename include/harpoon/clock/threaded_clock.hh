#ifndef HARPOON_CLOCK_THREADED_CLOCK_HH
#define HARPOON_CLOCK_THREADED_CLOCK_HH

#include "harpoon/harpoon.hh"

#include "harpoon/clock/clock.hh"

#include <atomic>
#include <thread>

namespace harpoon {
namespace clock {

class threaded_clock : public clock {
public:
	using clock::clock;
	threaded_clock(const threaded_clock &) = delete;
	threaded_clock &operator=(const threaded_clock &) = delete;

	virtual ~threaded_clock() override;

	virtual void prepare() override;
	virtual void boot() override;
	virtual void shutdown() override;

	virtual void log_state(log::message::Level level) const override;

private:
	std::unique_ptr<std::thread> _thread{};
	std::atomic_uint_fast64_t _missed_ticks{};
};

using threaded_clock_ptr = std::shared_ptr<threaded_clock>;

template<typename... Args>
threaded_clock_ptr make_threaded_clock(Args &&... args) {
	return std::make_shared<threaded_clock>(std::forward<Args>(args)...);
}

} // namespace clock
} // namespace harpoon

#endif
