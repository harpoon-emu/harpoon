#ifndef CPU_INSTRUCTIONS_SED_HH
#define CPU_INSTRUCTIONS_SED_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class sed : public mos_6510_nullary_instruction<0xF8, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.D() = true;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "SED");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
