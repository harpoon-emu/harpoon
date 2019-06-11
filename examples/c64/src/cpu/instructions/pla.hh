#ifndef CPU_INSTRUCTIONS_PLA_HH
#define CPU_INSTRUCTIONS_PLA_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class pla : public mos_6510_a_nullary_instruction<0x68, 4> {
public:
	void execute() {
		pop(get_cpu()->get_registers().A);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "PLA");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
