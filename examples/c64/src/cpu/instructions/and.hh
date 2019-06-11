#ifndef CPU_INSTRUCTIONS_AND_HH
#define CPU_INSTRUCTIONS_AND_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class and_op : public mos_6510_a_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_and(std::uint8_t val) {
		this->get_cpu()->get_registers().A &= val;
		this->update_flags_NZ(this->get_cpu());
	}
};

class and_immediate : public and_op<0x29, std::uint8_t, 2> {
public:
	void execute() {
		do_and(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "AND");
	}
};

class and_zero_page : public and_op<0x25, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "AND");
	}
};

class and_zero_page_x : public and_op<0x35, std::uint8_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "AND");
	}
};

class and_absolute : public and_op<0x2D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "AND");
	}
};

class and_absolute_x : public and_op<0x3D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "AND");
	}
};

class and_absolute_y : public and_op<0x39, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_y(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "AND");
	}
};

class and_indirect_x : public and_op<0x21, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_x(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "AND");
	}
};

class and_indirect_y : public and_op<0x31, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_y(val);
		do_and(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "AND");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
