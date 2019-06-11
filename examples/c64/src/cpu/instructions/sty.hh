#ifndef CPU_INSTRUCTIONS_STY_HH
#define CPU_INSTRUCTIONS_STY_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class sty_zero_page : public mos_6510_unary_instruction<0x84, std::uint8_t, 3> {
public:
	void execute() {
		set_zero_page(get_cpu()->get_registers().Y);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "STY");
	}
};

class sty_zero_page_x : public mos_6510_unary_instruction<0x94, std::uint8_t, 4> {
public:
	void execute() {
		set_zero_page_x(get_cpu()->get_registers().Y);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "STY");
	}
};

class sty_absolute : public mos_6510_unary_instruction<0x8C, std::uint16_t, 4> {
public:
	void execute() {
		set_absolute(get_cpu()->get_registers().Y);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "STY");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
