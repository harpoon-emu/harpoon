#include "harpoon/execution/processing_unit.hh"

#include "harpoon/execution/exception/execution_exception.hh"

#include <iomanip>

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
	_run_start = std::chrono::high_resolution_clock::now();
	new_stats_checkpoint();
}

void processing_unit::shutdown() {
	log(component_notice << "Executed " << _executed_instructions << " instructions");

	hardware_component::shutdown();
}

std::uint32_t processing_unit::execute_instruction() {
	if (_current_instruction.done()) {
		throw COMPONENT_EXCEPTION(exception::execution_exception, "Broken execution flow.");
	}

	return _current_instruction.step();
}

void processing_unit::disassemble_instruction() {
	std::stringstream stream;
	_current_instruction.disassemble(stream);
	log(component_debug << std::hex << std::setw(8) << std::setfill('0') << std::uppercase
	                    << _executed_instructions << " | " << stream.str());
}

void processing_unit::log_state(harpoon::log::message::Level level) const {
	hardware_component::log_state(level);
	log(component_log(level) << "Executed instructions: " << _executed_instructions);
	log_registers(level);
}

void processing_unit::log_registers(harpoon::log::message::Level) const {}

void processing_unit::new_stats_checkpoint() {
	_stats_checkpoint_executed_instruction = _executed_instructions;
	_stats_checkpoint_start = std::chrono::high_resolution_clock::now();
}

void processing_unit::log_stats(harpoon::log::message::Level level) {

	std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
	std::uint64_t ms = static_cast<std::uint64_t>(
	    std::chrono::duration_cast<std::chrono::milliseconds>(t - _stats_checkpoint_start).count());
	std::uint64_t ms_t = static_cast<std::uint64_t>(
	    std::chrono::duration_cast<std::chrono::milliseconds>(t - _run_start).count());

	log(component_log(level) << "Executed instructions (checkpoint / total): "
	                         << _executed_instructions - _stats_checkpoint_executed_instruction
	                         << " / " << _executed_instructions);
	if (ms > 0) {
		log(component_log(level) << "Instructions per second (checkpoint / total): "
		                         << static_cast<double>(_executed_instructions
		                                                - _stats_checkpoint_executed_instruction)
		                                / ms * 1000
		                         << " / "
		                         << static_cast<double>(_executed_instructions) / ms_t * 1000);
	}
}

} // namespace execution
} // namespace harpoon
