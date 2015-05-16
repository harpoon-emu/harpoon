#ifndef HARPOON_CLOCK_GENERATOR_DUMMY_GENERATOR_HH
#define HARPOON_CLOCK_GENERATOR_DUMMY_GENERATOR_HH

#include "harpoon/harpoon.hh"
#include "harpoon/clock/generator/generator.hh"

namespace harpoon {
namespace clock {
namespace generator {

class dummy_generator : public generator {
public:

	using generator::generator;

	virtual ~dummy_generator();

	void wait_for_tick(std::uint64_t tick) {
		while (get_atomic_tick().load() < tick) {
			this->tick();
		}
	}

	void wait_tick(std::uint64_t tick_count = 1) {
		wait_for_tick(get_atomic_tick().load() + tick_count);
	}

};

}
}
}

#endif