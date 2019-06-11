#ifndef CPU_INSTRUCTIONS_DEC_HH
#define CPU_INSTRUCTIONS_DEC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class dec : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_dec(std::uint8_t &val) {
		val--;
		this->update_flags_NZ(this->get_cpu(), val);
	}
};

class dec_zero_page : public dec<0xC6, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t m{};
		get_zero_page(m);
		do_dec(m);
		set_zero_page(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "DEC");
	}
};

class dec_zero_page_x : public dec<0xD6, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t m{};
		get_zero_page_x(m);
		do_dec(m);
		set_zero_page_x(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "DEC");
	}
};

class dec_absolute : public dec<0xCE, std::uint16_t, 6> {
public:
	void execute() {
		std::uint8_t m{};
		get_absolute(m);
		do_dec(m);
		set_absolute(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "DEC");
	}
};

class dec_absolute_x : public dec<0xDE, std::uint16_t, 7> {
public:
	void execute() {
		std::uint8_t m{};
		get_absolute_x(m);
		do_dec(m);
		set_absolute_x(m);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "DEC");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
