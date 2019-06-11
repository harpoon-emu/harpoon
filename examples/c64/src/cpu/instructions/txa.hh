#ifndef CPU_INSTRUCTIONS_TXA_HH
#define CPU_INSTRUCTIONS_TXA_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class txa : public mos_6510_a_nullary_instruction<0x8A, 2> {
public:
	void execute() {
		get_cpu()->get_registers().A = get_cpu()->get_registers().X;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "TXA");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
