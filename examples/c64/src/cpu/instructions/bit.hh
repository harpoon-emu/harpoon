#ifndef CPU_INSTRUCTIONS_BIT_HH
#define CPU_INSTRUCTIONS_BIT_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class bit : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
public:
	void disassemble(std::ostream &stream) const {
		this->mos_disassemble_absolute(stream, "BIT");
	}

protected:
	void do_bit(std::uint8_t val) {
		std::uint8_t res = this->get_cpu()->get_registers().A & val;
		this->update_flags_NZ(this->get_cpu(), res);
		this->get_cpu()->get_registers().P.V() = ((res & 0x40) == 0x40);
	}
};

class bit_zero_page : public bit<0x24, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_bit(val);
	}
};

class bit_absolute : public bit<0x2C, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_bit(val);
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
