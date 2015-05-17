#include "harpoon/execution/cpu.hh"

using namespace harpoon::execution;

cpu::~cpu() {}

void cpu::prepare() {
	_execution_unit = std::dynamic_pointer_cast<execution_unit>(get_parent_component());
	hardware_component::prepare();
}

void cpu::boot() {
	hardware_component::boot();

	_executed_instructions = 0;
	_cycle = 0;
	_last_tick = get_execution_unit()->get_clock()->get_tick();

	_running = true;

	_thread.reset(new std::thread([this]() {
		run();
	}));
}

void cpu::shutdown() {
	_running = false;
	if (_thread) {
		_thread->join();
	}

	log(component_notice << "Stopped after " << _cycle << " cycles");
	log(component_notice << "Executed " << _executed_instructions << " instructions");

	hardware_component::shutdown();
}

void cpu::run() {

	log(component_notice << "Running CPU loop");

	const auto& execution_unit = get_execution_unit();

	while (is_running()) {
		if (execution_unit->is_running()) {
			wait_for_cycle(fetch());
			if (execution_unit->is_running()) {
				wait_for_cycle(execute());
				++_executed_instructions;
			}
		} else {
			wait_for_next_cycle();
		}
	}

	log(component_notice << "Exiting CPU loop");

}

cycle cpu::wait_for_cycle(std::uint_fast64_t cycles) {
	_last_tick = get_execution_unit()->get_clock()->wait_for_tick(_last_tick + cycles);
	if (get_execution_unit()->get_clock()->is_running()) {
		_cycle += cycles;
	}
	return _cycle;
}
