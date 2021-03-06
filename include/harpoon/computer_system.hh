#ifndef HARPOON_COMPUTER_SYSTEM_HH
#define HARPOON_COMPUTER_SYSTEM_HH

#include "harpoon/harpoon.hh"

#include "harpoon/execution/execution_unit.hh"
#include "harpoon/hardware_component.hh"
#include "harpoon/memory/memory.hh"

namespace harpoon {

class computer_system : public hardware_component {
public:
	using hardware_component::hardware_component;

	void set_main_execution_unit(const execution::execution_unit_ptr &main_execution_unit);

	const execution::execution_unit_ptr &get_main_execution_unit() const {
		return _main_execution_unit;
	}

	void set_main_memory(const memory::memory_ptr &main_memory);

	memory::memory_ptr get_main_memory() const {
		return _main_memory;
	}

	virtual void step(hardware_component *trigger) override;

	virtual void run();

	virtual ~computer_system() override;

private:
	execution::execution_unit_ptr _main_execution_unit{};
	memory::memory_ptr _main_memory{};
};

using computer_system_ptr = std::shared_ptr<computer_system>;

template<typename... Args>
computer_system_ptr make_computer_system(Args &&... args) {
	return std::make_shared<computer_system>(std::forward<Args>(args)...);
}

} // namespace harpoon

#endif
