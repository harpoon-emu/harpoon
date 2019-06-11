#ifndef CPU_INSTRUCTIONS_ASL_HH
#define CPU_INSTRUCTIONS_ASL_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class asl : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_asl(std::uint8_t &val) {
		this->get_cpu()->get_registers().P.C() = ((val & 0x80) == 0x80);
		val <<= 1;
		this->update_flags_NZ(this->get_cpu(), val);
	}
};

class asl_accumulator : public mos_6510_a_nullary_instruction<0x0A, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.C() = ((get_cpu()->get_registers().A & 0x80) == 0x80);
		get_cpu()->get_registers().A <<= 1;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "ASL");
	}
};

class asl_zero_page : public asl<0x06, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_asl(val);
		set_zero_page(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ASL");
	}
};

class asl_zero_page_x : public asl<0x16, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_asl(val);
		set_zero_page_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ASL");
	}
};

class asl_absolute : public asl<0x0E, std::uint16_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_asl(val);
		set_absolute(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ASL");
	}
};

class asl_absolute_x : public asl<0x1E, std::uint16_t, 7> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_asl(val);
		set_absolute_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ASL");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
