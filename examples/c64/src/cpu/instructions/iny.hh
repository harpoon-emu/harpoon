#ifndef CPU_INSTRUCTIONS_INY_HH
#define CPU_INSTRUCTIONS_INY_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class iny : public mos_6510_y_nullary_instruction<0xC8, 2> {
public:
	void execute() {
		get_cpu()->get_registers().Y++;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "INY");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
