#ifndef HARPOON_CLOCK_CLOCK_HH
#define HARPOON_CLOCK_CLOCK_HH

#include "harpoon/harpoon.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace clock {

template<std::uint32_t frequency, typename Generator>
class clock : public hardware_component {
public:

	using hardware_component::hardware_component;
	clock(const std::string& name = "") : hardware_component(name) {}

	virtual ~clock() {};

	const Generator& get_generator() const {
		return _generator;
	}

	Generator& get_generator() {
		return _generator;
	}

	std::uint64_t get_tick() const {
		return _generator.get_tick();
	}

	void wait_for_tick(std::uint64_t tick) {
		_generator.wait_for_tick(tick);
	}

	void wait_tick(std::uint64_t tick_count = 1) {
		_generator.wait_tick(tick_count);
	}

	void start() {
		_generator.start();
	}
	void stop() {
		_generator.stop();
	}

	virtual void boot() {
		start();
	}
	virtual void shutdown() {
		stop();
	}

private:
	Generator _generator{frequency};
};

template<std::uint32_t frequency, typename Generator>
using clock_ptr = std::shared_ptr<clock<frequency, Generator>>;
template<std::uint32_t frequency, typename Generator, typename... Args>
clock_ptr<frequency, Generator> make_clock(Args&&... args) {
	return std::make_shared<clock<frequency, Generator>>(std::forward<Args>(args)...);
}


}
}

#endif