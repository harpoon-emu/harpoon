#include "harpoon/execution/processing_unit.hh"

#include "harpoon/execution/exception/execution_exception.hh"

namespace harpoon {
namespace execution {

processing_unit::~processing_unit() {}

void processing_unit::prepare() {
	_execution_unit = std::dynamic_pointer_cast<execution_unit>(get_parent_component());
	hardware_component::prepare();
}

void processing_unit::boot() {
	hardware_component::boot();

	_executed_instructions = 0;
	_cycle = 0;
	_last_tick = get_execution_unit()->get_clock()->get_tick();

	_running = true;

	_thread.reset(new std::thread([this]() { run(); }));
}

void processing_unit::shutdown() {
	_running = false;
	if (_thread) {
		_thread->join();
	}

	log(component_notice << "Stopped after " << _cycle << " cycles");
	log(component_notice << "Executed " << _executed_instructions << " instructions");

	hardware_component::shutdown();
}

void processing_unit::run() {

	log(component_notice << "Running processing loop");

	const auto &execution_unit = get_execution_unit();

	wait_for_cycle(begin_execution());

	try {
		while (is_running()) {
			if (execution_unit->is_running()) {
				instruction_handler instruction_handler;
				disassemble_handler disassemble_handler;

				for (const auto &breakpoint : _breakpoints) {
					if (breakpoint.check_condition(this)) {
						log(component_debug << "EXECUTION BREAKPOINT");
						breakpoint.do_action(this);
					}
				}

				wait_for_cycle(fetch_decode(instruction_handler, disassemble_handler));

				if (_disassemble) {
					std::stringstream stream;
					disassemble_handler(stream);
					log(component_debug << stream.str());
				}

				if (execution_unit->is_running()) {
					wait_for_cycle(execute(instruction_handler));
					++_executed_instructions;
				}
			} else {
				wait_for_next_cycle();
			}
		}
	} catch (const exception::execution_exception &error) {
		log(component_error << "Execution exception: " << error.what());
		log_state();
	}

	log(component_notice << "Exiting processing loop");
}

std::uint_fast64_t processing_unit::execute(instruction_handler &instruction_handler) {
	return instruction_handler(this);
}

cycle processing_unit::wait_for_cycle(std::uint_fast64_t cycles) {
	_last_tick = get_execution_unit()->get_clock()->wait_for_tick(_last_tick + cycles);
	if (get_execution_unit()->get_clock()->is_running()) {
		_cycle += cycles;
	}
	return _cycle;
}

void processing_unit::log_state(harpoon::log::message::Level level) const {
	hardware_component::log_state(level);
	log(component_log(level) << "Current cycle: " << _cycle);
	log(component_log(level) << "Executed instructions: " << _executed_instructions);
	log_registers(level);
}

void processing_unit::log_registers(harpoon::log::message::Level) const {}

} // namespace execution
} // namespace harpoon
