#ifndef CPU_INSTRUCTIONS_JSR_HH
#define CPU_INSTRUCTIONS_JSR_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class jsr : public mos_6510_unary_instruction<0x20, std::uint16_t, 6> {
public:
	void execute() {
		push(static_cast<std::uint16_t>(get_cpu()->get_registers().PC - 1));
		get_cpu()->get_registers().PC = _operand;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "JSR");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
