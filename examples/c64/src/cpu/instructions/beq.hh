#ifndef CPU_INSTRUCTIONS_BEQ_HH
#define CPU_INSTRUCTIONS_BEQ_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class beq : public mos_6510_relative_branch_instruction<0xF0, 3> {
public:
	void execute() {
		branch(get_cpu()->get_registers().P.Z());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_relative(stream, "BEQ");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
