#ifndef CPU_INSTRUCTIONS_LDX_HH
#define CPU_INSTRUCTIONS_LDX_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class ldx : public mos_6510_x_unary_instruction<OP, OPERAND, CYCLES> {};

class ldx_immediate : public ldx<0xA2, std::uint8_t, 2> {
public:
	void execute() {
		get_cpu()->get_registers().X = _operand;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "LDX");
	}
};

class ldx_zero_page : public ldx<0xA6, std::uint8_t, 3> {
public:
	void execute() {
		get_zero_page(get_cpu()->get_registers().X);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "LDX");
	}
};

class ldx_zero_page_y : public ldx<0xB6, std::uint8_t, 4> {
public:
	void execute() {
		get_zero_page_y(get_cpu()->get_registers().X);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "LDX");
	}
};

class ldx_absolute : public ldx<0xAE, std::uint16_t, 4> {
public:
	void execute() {
		get_absolute(get_cpu()->get_registers().X);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "LDX");
	}
};

class ldx_absolute_y : public ldx<0xBE, std::uint16_t, 4> {
public:
	void execute() {
		get_absolute_y(get_cpu()->get_registers().X);
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "LDX");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
