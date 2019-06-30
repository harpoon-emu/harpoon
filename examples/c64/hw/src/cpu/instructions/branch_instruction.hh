#ifndef CPU_INSTRUCTIONS_BRANCH_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_BRANCH_INSTRUCTION_HH

#include "../mos_6510.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<bool (mos_6510::*get_flag)() const, bool V>
class branch_on : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		if ((get_cpu()->*get_flag)() == V) {
			std::uint32_t delay = 1;
			std::int16_t pc = static_cast<std::int16_t>(get_cpu()->get_PC());
			std::int8_t offset
			    = static_cast<std::int8_t>(get_cpu()->get_internal_memory_access().b.current);
			get_cpu()->set_PC(static_cast<std::uint16_t>(pc + offset));
			delay++;
			if ((pc & 0xFF) != (get_cpu()->get_PC() & 0xFF)) {
				delay++;
			}
			set_delay(delay);
		}
		get_cpu()->fetch_opcode();
	}
};

template<bool (mos_6510::*get_flag)() const, bool V>
harpoon::execution::instruction relative_branch_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(cpu, {make_instruction_step<fetch_program_code>(),
	                                             make_instruction_step<branch_on<get_flag, V>>()});
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
