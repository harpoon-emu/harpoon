#ifndef CPU_INSTRUCTIONS_CPX_HH
#define CPU_INSTRUCTIONS_CPX_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class cpx : public mos_6510_x_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_cpx(std::uint8_t val) {
		std::uint8_t x = this->get_cpu()->get_registers().X;
		std::uint8_t y = val;
		std::uint8_t res = x - y;
		this->get_cpu()->get_registers().P.N() = ((res & 0x80) == 0x80);
		this->get_cpu()->get_registers().P.Z() = (res == 0x00);
		this->get_cpu()->get_registers().P.C() = (x >= y);
	}
};

class cpx_immediate : public cpx<0xE0, std::uint8_t, 2> {
public:
	void execute() {
		do_cpx(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "CPX");
	}
};

class cpx_zero_page : public cpx<0xE4, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t mem{};
		get_zero_page(mem);
		do_cpx(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "CPX");
	}
};

class cpx_absolute : public cpx<0xEC, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t mem{};
		get_absolute(mem);
		do_cpx(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "CPX");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
