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

} // namespace execution
} // namespace harpoon
