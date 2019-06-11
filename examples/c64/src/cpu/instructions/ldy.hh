#ifndef CPU_INSTRUCTIONS_LDY_HH
#define CPU_INSTRUCTIONS_LDY_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class ldy : public mos_6510_y_unary_instruction<OP, OPERAND, CYCLES> {};

class ldy_immediate : public ldy<0xA0, std::uint8_t, 2> {
public:
	void execute() {
		get_cpu()->get_registers().Y = _operand;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "LDY");
	}
};

class ldy_zero_page : public ldy<0xA4, std::uint8_t, 3> {
public:
	void execute() {
		get_zero_page(get_cpu()->get_registers().Y);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "LDY");
	}
};

class ldy_zero_page_x : public ldy<0xB4, std::uint8_t, 4> {
public:
	void execute() {
		get_zero_page_x(get_cpu()->get_registers().Y);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "LDY");
	}
};

class ldy_absolute : public ldy<0xAC, std::uint16_t, 4> {
public:
	void execute() {
		get_absolute(get_cpu()->get_registers().Y);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "LDY");
	}
};

class ldy_absolute_x : public ldy<0xBC, std::uint16_t, 4> {
public:
	void execute() {
		get_absolute_x(get_cpu()->get_registers().Y);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "LDY");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
