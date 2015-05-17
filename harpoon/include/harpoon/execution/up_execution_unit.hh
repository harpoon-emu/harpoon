#ifndef HARPOON_EXECUTION_UP_EXECUTION_UNIT_HH
#define HARPOON_EXECUTION_UP_EXECUTION_UNIT_HH

#include "harpoon/harpoon.hh"
#include "harpoon/execution/execution_unit.hh"
#include "harpoon/execution/cpu.hh"

namespace harpoon {
namespace execution {

class up_execution_unit : public execution_unit {
public:

	using execution_unit::execution_unit;

	virtual ~up_execution_unit() {};

	void set_cpu(const cpu_ptr& cpu) {
		replace_component(_cpu, cpu);
		_cpu = cpu;
	}

	cpu_ptr get_cpu() const {
		return _cpu.lock();
	}

private:
	cpu_weak_ptr _cpu{};
};

using up_execution_unit_ptr = std::shared_ptr<up_execution_unit>;
using up_execution_unit_weak_ptr = std::weak_ptr<up_execution_unit>;
template<typename... Args>
up_execution_unit_ptr make_up_execution_unit(Args&&... args) {
	return std::make_shared<up_execution_unit>(std::forward<Args>(args)...);
}

}
}

#endif