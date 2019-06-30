#include "instruction_step.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

instruction_step::~instruction_step() {}

std::uint32_t instruction_step_read::check() {
	return 0;
}

std::uint32_t instruction_step_fetch_next::step() {
	get_cpu()->fetch_opcode();
	return instruction_step_read::step();
}

std::uint32_t instruction_step_write::check() {
	return 0;
}

void internal_read::execute() {}

void internal_write::execute() {}

void fetch_program_code::execute() {
	get_cpu()->internal_read_program_code();
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
