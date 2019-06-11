#ifndef CPU_INSTRUCTIONS_ORA_HH
#define CPU_INSTRUCTIONS_ORA_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class ora : public mos_6510_a_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_ora(std::uint8_t val) {
		this->get_cpu()->get_registers().A |= val;
		this->update_flags_NZ(this->get_cpu());
	}
};

class ora_immediate : public ora<0x09, std::uint8_t, 2> {
public:
	void execute() {
		do_ora(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "ORA");
	}
};

class ora_zero_page : public ora<0x05, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ORA");
	}
};

class ora_zero_page_x : public ora<0x15, std::uint8_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ORA");
	}
};

class ora_absolute : public ora<0x0D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ORA");
	}
};

class ora_absolute_x : public ora<0x1D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ORA");
	}
};

class ora_absolute_y : public ora<0x19, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_y(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "ORA");
	}
};

class ora_indirect_x : public ora<0x01, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_x(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "ORA");
	}
};

class ora_indirect_y : public ora<0x11, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_y(val);
		do_ora(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "ORA");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
