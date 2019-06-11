#ifndef CPU_INSTRUCTIONS_SEI_HH
#define CPU_INSTRUCTIONS_SEI_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class sei : public mos_6510_nullary_instruction<0x78, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.I() = true;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "SEI");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
