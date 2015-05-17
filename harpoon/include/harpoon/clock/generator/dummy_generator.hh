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

	tick wait_for_tick(tick tick) {
		while (get_atomic_tick() < tick) {
			this->next_tick();
		}
		return get_atomic_tick();
	}

	tick wait_tick(std::uint_fast64_t tick_count = 1) {
		return wait_for_tick(get_atomic_tick().load() + tick_count);
	}

};

using dummy_generator_ptr = std::shared_ptr<dummy_generator>;
using dummy_generator_weak_ptr = std::weak_ptr<dummy_generator>;
template<typename... Args>
dummy_generator_ptr make_dummy_generator(Args&&... args) {
	return std::make_shared<dummy_generator>(std::forward<Args>(args)...);
}

}
}
}

#endif