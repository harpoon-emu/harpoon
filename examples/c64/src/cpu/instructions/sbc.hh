#ifndef CPU_INSTRUCTIONS_SBC_HH
#define CPU_INSTRUCTIONS_SBC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class sbc : public mos_6510_a_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_sbc(std::uint8_t val) {
		std::uint8_t x = this->get_cpu()->get_registers().A;
		std::uint8_t y = ~val;
		std::uint16_t res = {};
		res = x + y;
		if (this->get_cpu()->get_registers().P.C()) {
			res++;
		}
		this->get_cpu()->get_registers().A = (res & 0xff);
		this->update_flags_NZ(this->get_cpu());
		this->get_cpu()->get_registers().P.V() = (((~(x ^ y)) & (x ^ res) & 0x80) == 0x80);
		this->get_cpu()->get_registers().P.C() = (res > 0xff);
	}
};

class sbc_immediate : public sbc<0xE9, std::uint8_t, 2> {
public:
	void execute() {
		do_sbc(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "SBC");
	}
};

class sbc_zero_page : public sbc<0xE5, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "SBC");
	}
};

class sbc_zero_page_x : public sbc<0xF5, std::uint8_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "SBC");
	}
};

class sbc_absolute : public sbc<0xED, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "SBC");
	}
};

class sbc_absolute_x : public sbc<0xFD, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "SBC");
	}
};

class sbc_absolute_y : public sbc<0xF9, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_y(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "SBC");
	}
};

class sbc_indirect_x : public sbc<0xE1, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_x(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "SBC");
	}
};

class sbc_indirect_y : public sbc<0xF1, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_y(val);
		do_sbc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "SBC");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
