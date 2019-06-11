#ifndef HARPOON_CLOCK_CLOCK_HH
#define HARPOON_CLOCK_CLOCK_HH

#include "harpoon/harpoon.hh"

#include "harpoon/clock/tick.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace clock {

class clock : public hardware_component {
public:
	using hardware_component::hardware_component;
	clock(std::uint32_t frequency = 1, const std::string &name = "")
	    : hardware_component(name), _frequency(frequency) {}

	void set_frequency(std::uint32_t frequency) {
		_frequency = frequency;
	}

	std::uint32_t get_frequency() const {
		return _frequency;
	}

	virtual tick get_tick() const = 0;
	virtual tick wait_for_tick(tick tick) = 0;
	virtual tick wait_tick(std::uint_fast64_t tick_count = 1) = 0;

	virtual void boot() override;
	virtual void shutdown() override;

	virtual void log_state(log::message::Level level) const override;

	virtual ~clock() override;

private:
	std::uint32_t _frequency{};
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
