#ifndef CPU_INSTRUCTIONS_CLD_HH
#define CPU_INSTRUCTIONS_CLD_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class cld : public mos_6510_nullary_instruction<0xD8, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.D() = false;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "CLD");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
