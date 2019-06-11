#ifndef CPU_INSTRUCTIONS_ROL_HH
#define CPU_INSTRUCTIONS_ROL_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class rol : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_rol(std::uint8_t &val) {
		bool new_C = ((val & 0x80) == 0x80);
		val <<= 1;
		val |= (this->get_cpu()->get_registers().P.C() ? 0x01 : 0);
		this->get_cpu()->get_registers().P.C() = new_C;
		this->update_flags_NZ(this->get_cpu(), val);
	}
};

class rol_accumulator : public mos_6510_a_nullary_instruction<0x2A, 2> {
public:
	void execute() {
		bool new_C = ((get_cpu()->get_registers().A & 0x80) == 0x80);
		get_cpu()->get_registers().A <<= 1;
		get_cpu()->get_registers().A |= (get_cpu()->get_registers().P.C() ? 0x01 : 0);
		get_cpu()->get_registers().P.C() = new_C;
		update_flags_NZ(get_cpu());
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "ROL");
	}
};

class rol_zero_page : public rol<0x26, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_rol(val);
		set_zero_page(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ROL");
	}
};

class rol_zero_page_x : public rol<0x36, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_rol(val);
		set_zero_page_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ROL");
	}
};

class rol_absolute : public rol<0x2E, std::uint16_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_rol(val);
		set_absolute(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ROL");
	}
};

class rol_absolute_x : public rol<0x3E, std::uint16_t, 7> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_rol(val);
		set_absolute_x(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ROL");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
