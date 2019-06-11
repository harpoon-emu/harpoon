#ifndef CPU_INSTRUCTIONS_BPL_HH
#define CPU_INSTRUCTIONS_BPL_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class bpl : public mos_6510_relative_branch_instruction<0x10, 3> {
public:
	void execute() {
		branch(!get_cpu()->get_registers().P.N());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_relative(stream, "BPL");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
