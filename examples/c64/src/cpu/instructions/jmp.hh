#ifndef CPU_INSTRUCTIONS_JMP_HH
#define CPU_INSTRUCTIONS_JMP_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class jmp_absolute : public mos_6510_unary_instruction<0x4C, std::uint16_t, 3> {
public:
	void execute() {
		get_cpu()->get_registers().PC = _operand;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "JMP");
	}
};

class jmp_indirect : public mos_6510_unary_instruction<0x6C, std::uint16_t, 5> {
public:
	void execute() {
		std::uint16_t ptr{};
		get_absolute(ptr);
		get_cpu()->get_registers().PC = ptr;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect(stream, "JMP");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
