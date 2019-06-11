#ifndef CPU_INSTRUCTIONS_LSR_HH
#define CPU_INSTRUCTIONS_LSR_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class lsr : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_lsr(std::uint8_t &val) {
		this->get_cpu()->get_registers().P.C() = ((val & 0x01) == 0x01);
		val >>= 1;
		this->update_flags_NZ(this->get_cpu(), val);
	}
};

class lsr_accumulator : public mos_6510_a_nullary_instruction<0x4A, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.C() = ((get_cpu()->get_registers().A & 0x01) == 0x01);
		get_cpu()->get_registers().A >>= 1;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "LSR");
	}
};

class lsr_zero_page : public lsr<0x46, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_lsr(val);
		set_zero_page(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "LSR");
	}
};

class lsr_zero_page_x : public lsr<0x56, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_lsr(val);
		set_zero_page_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "LSR");
	}
};

class lsr_absolute : public lsr<0x4E, std::uint16_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_lsr(val);
		set_absolute(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "LSR");
	}
};

class lsr_absolute_x : public lsr<0x5E, std::uint16_t, 7> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_lsr(val);
		set_absolute_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "LSR");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
