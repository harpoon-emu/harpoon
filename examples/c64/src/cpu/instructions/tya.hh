#ifndef CPU_INSTRUCTIONS_TYA_HH
#define CPU_INSTRUCTIONS_TYA_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class tya : public mos_6510_a_nullary_instruction<0x98, 2> {
public:
	void execute() {
		get_cpu()->get_registers().A = get_cpu()->get_registers().Y;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "TYA");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
