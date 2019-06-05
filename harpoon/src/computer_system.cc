#include "harpoon/computer_system.hh"

namespace harpoon {

computer_system::~computer_system() {
}

void computer_system::set_main_execution_unit(const execution::execution_unit_weak_ptr& main_execution_unit) {
	replace_component(_main_execution_unit, main_execution_unit);
	_main_execution_unit = main_execution_unit;
}

void computer_system::set_main_memory(const memory::memory_weak_ptr& main_memory) {
	replace_component(_main_memory, main_memory);
	_main_memory = main_memory;
}

void computer_system::run() {}

}
