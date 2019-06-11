#ifndef CPU_INSTRUCTIONS_INC_HH
#define CPU_INSTRUCTIONS_INC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class inc : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_inc(std::uint8_t &val) {
		val++;
		this->update_flags_NZ(this->get_cpu(), val);
	}
};

class inc_zero_page : public inc<0xE6, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t m{};
		get_zero_page(m);
		do_inc(m);
		set_zero_page(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "INC");
	}
};

class inc_zero_page_x : public inc<0xF6, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t m{};
		get_zero_page_x(m);
		do_inc(m);
		set_zero_page_x(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "INC");
	}
};

class inc_absolute : public inc<0xEE, std::uint16_t, 6> {
public:
	void execute() {
		std::uint8_t m{};
		get_absolute(m);
		do_inc(m);
		set_absolute(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "INC");
	}
};

class inc_absolute_x : public inc<0xFE, std::uint16_t, 7> {
public:
	void execute() {
		std::uint8_t m{};
		get_absolute_x(m);
		do_inc(m);
		set_absolute_x(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "INC");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
