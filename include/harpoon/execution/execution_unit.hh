#ifndef HARPOON_EXECUTION_EXECUTION_UNIT_HH
#define HARPOON_EXECUTION_EXECUTION_UNIT_HH

#include "harpoon/harpoon.hh"

#include "harpoon/clock/clock.hh"
#include "harpoon/hardware_component.hh"

namespace harpoon {
namespace execution {

class execution_unit : public hardware_component {
public:
	using hardware_component::hardware_component;

	void set_clock(const clock::clock_ptr &clock);

	clock::clock_ptr get_clock() const {
		return _clock.lock();
	}

	virtual void step(hardware_component *trigger) override;

	virtual void enable_disassemble() = 0;
	virtual void disable_disassemble() = 0;

	void set_disassemble(bool d) {
		if (d) {
			enable_disassemble();
		} else {
			disable_disassemble();
		}
	}

	virtual ~execution_unit() override;

private:
	clock::clock_weak_ptr _clock{};
};

using execution_unit_ptr = std::shared_ptr<execution_unit>;
using execution_unit_weak_ptr = std::weak_ptr<execution_unit>;

} // namespace execution
} // namespace harpoon

#endif
