#ifndef CPU_INSTRUCTIONS_BNE_HH
#define CPU_INSTRUCTIONS_BNE_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class bne : public mos_6510_relative_branch_instruction<0xD0, 3> {
public:
	void execute() {
		branch(!get_cpu()->get_registers().P.Z());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_relative(stream, "BNE");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
