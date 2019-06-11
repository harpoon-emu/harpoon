#ifndef CPU_INSTRUCTIONS_CLC_HH
#define CPU_INSTRUCTIONS_CLC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class clc : public mos_6510_nullary_instruction<0x18, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.C() = false;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "CLC");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
