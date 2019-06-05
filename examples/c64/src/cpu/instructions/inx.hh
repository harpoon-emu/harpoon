#ifndef CPU_INSTRUCTIONS_INX_HH
#define CPU_INSTRUCTIONS_INX_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class inx : public mos_6510_x_nullary_instruction<0xE8, 2> {
public:
	void execute() {
		get_cpu()->get_registers().X++;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream& stream) const {
		mos_disassemble(stream, "INX");
	}
};

}
}
}

#endif
