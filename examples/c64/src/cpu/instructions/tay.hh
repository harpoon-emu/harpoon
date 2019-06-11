#ifndef CPU_INSTRUCTIONS_TAY_HH
#define CPU_INSTRUCTIONS_TAY_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class tay : public mos_6510_y_nullary_instruction<0xA8, 2> {
public:
	void execute() {
		get_cpu()->get_registers().Y = get_cpu()->get_registers().A;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "TAY");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
