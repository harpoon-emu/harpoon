#ifndef CPU_INSTRUCTIONS_ROR_HH
#define CPU_INSTRUCTIONS_ROR_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class ror : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_ror(std::uint8_t &val) {
		bool new_C = ((val & 0x01) == 0x01);
		val >>= 1;
		val |= (this->get_cpu()->get_registers().P.C() ? 0x80 : 0);
		this->get_cpu()->get_registers().P.C() = new_C;
		this->update_flags_NZ(this->get_cpu(), val);
	}
};

class ror_accumulator : public mos_6510_a_nullary_instruction<0x6A, 2> {
public:
	void execute() {
		bool new_C = ((get_cpu()->get_registers().A & 0x01) == 0x01);
		get_cpu()->get_registers().A >>= 1;
		get_cpu()->get_registers().A |= (get_cpu()->get_registers().P.C() ? 0x80 : 0);
		get_cpu()->get_registers().P.C() = new_C;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "ROR");
	}
};

class ror_zero_page : public ror<0x66, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_ror(val);
		set_zero_page(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ROR");
	}
};

class ror_zero_page_x : public ror<0x76, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_ror(val);
		set_zero_page_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ROR");
	}
};

class ror_absolute : public ror<0x6E, std::uint16_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_ror(val);
		set_absolute(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ROR");
	}
};

class ror_absolute_x : public ror<0x7E, std::uint16_t, 7> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_ror(val);
		set_absolute_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ROR");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
