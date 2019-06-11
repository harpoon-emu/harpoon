#ifndef CPU_INSTRUCTIONS_SEC_HH
#define CPU_INSTRUCTIONS_SEC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class sec : public mos_6510_nullary_instruction<0x38, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.C() = true;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "SEC");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
