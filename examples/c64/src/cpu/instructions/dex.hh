#ifndef CPU_INSTRUCTIONS_DEX_HH
#define CPU_INSTRUCTIONS_DEX_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class dex : public mos_6510_x_nullary_instruction<0xCA, 2> {
public:
	void execute() {
		get_cpu()->get_registers().X--;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "DEX");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
