#ifndef CPU_INSTRUCTIONS_STA_HH
#define CPU_INSTRUCTIONS_STA_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class sta_zero_page : public mos_6510_unary_instruction<0x85, std::uint8_t, 3> {
public:
	void execute() {
		set_zero_page(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "STA");
	}
};

class sta_zero_page_x : public mos_6510_unary_instruction<0x95, std::uint8_t, 4> {
public:
	void execute() {
		set_zero_page_x(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "STA");
	}
};

class sta_absolute : public mos_6510_unary_instruction<0x8D, std::uint16_t, 4> {
public:
	void execute() {
		set_absolute(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "STA");
	}
};

class sta_absolute_x : public mos_6510_unary_instruction<0x9D, std::uint16_t, 5> {
public:
	void execute() {
		set_absolute_x(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "STA");
	}
};

class sta_absolute_y : public mos_6510_unary_instruction<0x99, std::uint16_t, 5> {
public:
	void execute() {
		set_absolute_y(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "STA");
	}
};

class sta_indirect_x : public mos_6510_unary_instruction<0x81, std::uint8_t, 6> {
public:
	void execute() {
		set_indirect_x(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "STA");
	}
};

class sta_indirect_y : public mos_6510_unary_instruction<0x91, std::uint8_t, 6> {
public:
	void execute() {
		set_indirect_y(get_cpu()->get_registers().A);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "STA");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
