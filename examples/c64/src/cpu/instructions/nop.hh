#ifndef CPU_INSTRUCTIONS_NOP_HH
#define CPU_INSTRUCTIONS_NOP_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class nop : public mos_6510_nullary_instruction<0xEA, 2> {
public:
	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "NOP");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
