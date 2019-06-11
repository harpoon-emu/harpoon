#ifndef CPU_INSTRUCTIONS_BVC_HH
#define CPU_INSTRUCTIONS_BVC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class bvc : public mos_6510_relative_branch_instruction<0x50, 3> {
public:
	void execute() {
		branch(!get_cpu()->get_registers().P.V());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_relative(stream, "BVC");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
