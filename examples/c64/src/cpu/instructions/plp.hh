#ifndef CPU_INSTRUCTIONS_PLP_HH
#define CPU_INSTRUCTIONS_PLP_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class plp : public mos_6510_nullary_instruction<0x28, 4> {
public:
	void execute() {
		std::uint8_t val{};
		pop(val);
		get_cpu()->get_registers().P.set_flags(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "PLP");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
