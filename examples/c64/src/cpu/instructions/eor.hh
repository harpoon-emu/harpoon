#ifndef CPU_INSTRUCTIONS_EOR_HH
#define CPU_INSTRUCTIONS_EOR_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class eor : public mos_6510_a_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_eor(std::uint8_t val) {
		this->get_cpu()->get_registers().A ^= val;
		this->update_flags_NZ(this->get_cpu());
	}
};

class eor_immediate : public eor<0x49, std::uint8_t, 2> {
public:
	void execute() {
		do_eor(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "EOR");
	}
};

class eor_zero_page : public eor<0x45, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "EOR");
	}
};

class eor_zero_page_x : public eor<0x55, std::uint8_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "EOR");
	}
};

class eor_absolute : public eor<0x4D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "EOR");
	}
};

class eor_absolute_x : public eor<0x5D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "EOR");
	}
};

class eor_absolute_y : public eor<0x59, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_y(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "EOR");
	}
};

class eor_indirect_x : public eor<0x41, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_x(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "EOR");
	}
};

class eor_indirect_y : public eor<0x51, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_y(val);
		do_eor(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "EOR");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
