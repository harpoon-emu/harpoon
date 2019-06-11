#ifndef CPU_INSTRUCTIONS_TXS_HH
#define CPU_INSTRUCTIONS_TXS_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class txs : public mos_6510_nullary_instruction<0x9A, 2> {
public:
	void execute() {
		get_cpu()->get_registers().SP = get_cpu()->get_registers().X;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "TXS");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
