#include "harpoon/computer_system.hh"

#include "harpoon/exception/hardware_component_exception.hh"

namespace harpoon {

computer_system::~computer_system() {}

void computer_system::set_main_execution_unit(
    const execution::execution_unit_weak_ptr &main_execution_unit) {
	replace_component(_main_execution_unit, main_execution_unit);
	_main_execution_unit = main_execution_unit;
}

void computer_system::set_main_memory(const memory::memory_weak_ptr &main_memory) {
	replace_component(_main_memory, main_memory);
	_main_memory = main_memory;
}

void computer_system::step(hardware_component *) {
	_main_execution_unit.lock()->step(this);
}

void computer_system::run() {
	try {
		while (is_running()) {
			step(nullptr);
		}
	} catch (exception::hardware_component_exception &error) {
		get_log()->out(log_critical_c(error.get_component()) << error.what());
	} catch (std::exception &error) {
		get_log()->out(log_critical << error.what());
	}
}

} // namespace harpoon
