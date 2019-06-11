#ifndef CPU_INSTRUCTIONS_CPY_HH
#define CPU_INSTRUCTIONS_CPY_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class cpy : public mos_6510_y_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_cpy(std::uint8_t val) {
		std::uint8_t x = this->get_cpu()->get_registers().Y;
		std::uint8_t y = val;
		std::uint8_t res = x - y;
		this->get_cpu()->get_registers().P.N() = ((res & 0x80) == 0x80);
		this->get_cpu()->get_registers().P.Z() = (res == 0x00);
		this->get_cpu()->get_registers().P.C() = (x >= y);
	}
};

class cpy_immediate : public cpy<0xC0, std::uint8_t, 2> {
public:
	void execute() {
		do_cpy(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "CPY");
	}
};

class cpy_zero_page : public cpy<0xC4, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t mem{};
		get_zero_page(mem);
		do_cpy(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "CPY");
	}
};

class cpy_absolute : public cpy<0xCC, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t mem{};
		get_absolute(mem);
		do_cpy(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "CPY");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
