#ifndef HARPOON_CLOCK_GENERATOR_THREADED_GENERATOR_HH
#define HARPOON_CLOCK_GENERATOR_THREADED_GENERATOR_HH

#include "harpoon/harpoon.hh"
#include "harpoon/clock/generator/generator.hh"

#include <thread>

namespace harpoon {
namespace clock {
namespace generator {

class threaded_generator : public generator {
public:

	using generator::generator;
	threaded_generator(const threaded_generator&) = delete;
	threaded_generator& operator=(const threaded_generator&) = delete;

	virtual ~threaded_generator();

	virtual void start();
	virtual void stop();

private:
	std::unique_ptr<std::thread> _thread{};
};

}
}
}

#endif