#ifndef HARPOON_CLOCK_CLOCK_HH
#define HARPOON_CLOCK_CLOCK_HH

#include "harpoon/harpoon.hh"
#include "harpoon/hardware_component.hh"
#include "harpoon/clock/tick.hh"
#include "harpoon/clock/generator/generator.hh"

namespace harpoon {
namespace clock {

class clock : public hardware_component {
public:

	using hardware_component::hardware_component;
	clock(const generator::generator_ptr& generator, const std::string& name = "") 
		: hardware_component(name), _generator(generator) {}

	void set_generator(const generator::generator_ptr& generator) {
		_generator = generator;
	}

	tick get_tick() const {
		return _generator->get_tick();
	}

	tick wait_for_tick(tick tick) {
		return _generator->wait_for_tick(tick);
	}

	tick wait_tick(std::uint_fast64_t tick_count = 1) {
		return _generator->wait_tick(tick_count);
	}

	bool is_running() const {
		return _generator->is_running();
	}

	virtual void boot();
	virtual void shutdown();

	virtual ~clock();

private:
	generator::generator_ptr _generator{};
};

using clock_ptr = std::shared_ptr<clock>;
using clock_weak_ptr = std::weak_ptr<clock>;
template<typename... Args>
clock_ptr make_clock(Args&&... args) {
	return std::make_shared<clock>(std::forward<Args>(args)...);
}


}
}

#endif