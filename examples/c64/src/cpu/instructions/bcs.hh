#ifndef CPU_INSTRUCTIONS_BCS_HH
#define CPU_INSTRUCTIONS_BCS_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class bcs : public mos_6510_relative_branch_instruction<0xB0, 3> {
public:
	void execute() {
		branch(get_cpu()->get_registers().P.C());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_relative(stream, "BCS");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
