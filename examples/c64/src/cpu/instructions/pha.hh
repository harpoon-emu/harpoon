#ifndef CPU_INSTRUCTIONS_PHA_HH
#define CPU_INSTRUCTIONS_PHA_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class pha : public mos_6510_nullary_instruction<0x48, 3> {
public:
	void execute() {
		push(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "PHA");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
