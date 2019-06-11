#ifndef CPU_INSTRUCTIONS_TSX_HH
#define CPU_INSTRUCTIONS_TSX_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class tsx : public mos_6510_x_nullary_instruction<0xBA, 2> {
public:
	void execute() {
		get_cpu()->get_registers().X = get_cpu()->get_registers().SP;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "TSX");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
