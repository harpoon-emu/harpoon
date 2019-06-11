#ifndef CPU_INSTRUCTIONS_STX_HH
#define CPU_INSTRUCTIONS_STX_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class stx_zero_page : public mos_6510_unary_instruction<0x86, std::uint8_t, 3> {
public:
	void execute() {
		set_zero_page(get_cpu()->get_registers().X);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "STX");
	}
};

class stx_zero_page_y : public mos_6510_unary_instruction<0x96, std::uint8_t, 4> {
public:
	void execute() {
		set_zero_page_y(get_cpu()->get_registers().X);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "STX");
	}
};

class stx_absolute : public mos_6510_unary_instruction<0x8E, std::uint16_t, 4> {
public:
	void execute() {
		set_absolute(get_cpu()->get_registers().X);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "STX");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
