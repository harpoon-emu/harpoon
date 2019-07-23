#ifndef HARPOON_CLOCK_CLOCK_HH
#define HARPOON_CLOCK_CLOCK_HH

#include "harpoon/harpoon.hh"

#include "harpoon/clock/cycle.hh"
#include "harpoon/hardware_component.hh"

#include <functional>
#include <map>

namespace harpoon {
namespace clock {

class clock : public hardware_component {
public:
	using step_handler = std::function<void(clock *)>;

	using hardware_component::hardware_component;
	clock(std::uint64_t frequency = 1, const std::string &name = "")
	    : hardware_component(name), _frequency(frequency) {}

	void set_frequency(std::uint64_t frequency) {
		_frequency = frequency;
	}

	std::uint64_t get_frequency() const {
		return _frequency;
	}

	const cycle &get_cycle() const {
		return _cycle;
	}

	virtual void boot() override;
	virtual void shutdown() override;
	virtual void step(hardware_component *trigger) override;

	void schedule(std::uint64_t delay, std::uint64_t phase, step_handler &&fn);

	virtual void log_state(log::message::Level level) const override;

	virtual ~clock() override;

protected:
	void next_tick();

private:
	std::uint64_t _frequency{};
	cycle _cycle{};

	std::multimap<std::pair<std::uint64_t, std::uint64_t>, step_handler> _handlers{};
};

using clock_ptr = std::shared_ptr<clock>;
using clock_weak_ptr = std::weak_ptr<clock>;
template<typename... Args>
clock_ptr make_clock(Args &&... args) {
	return std::make_shared<clock>(std::forward<Args>(args)...);
}


} // namespace clock
} // namespace harpoon

#endif
