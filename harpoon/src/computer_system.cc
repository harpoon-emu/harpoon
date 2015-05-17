#include "harpoon/computer_system.hh"

using namespace harpoon;

computer_system::~computer_system() {
}

void computer_system::set_main_execution_unit(const execution::execution_unit_ptr& main_execution_unit) {
	replace_component(_main_execution_unit, main_execution_unit);
	_main_execution_unit = main_execution_unit;
}

void computer_system::run() {}