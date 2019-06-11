#ifndef CPU_INSTRUCTIONS_BVS_HH
#define CPU_INSTRUCTIONS_BVS_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class bvs : public mos_6510_relative_branch_instruction<0x70, 3> {
public:
	void execute() {
		branch(get_cpu()->get_registers().P.V());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_relative(stream, "BVS");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
