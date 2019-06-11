#ifndef CPU_INSTRUCTIONS_CLV_HH
#define CPU_INSTRUCTIONS_CLV_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class clv : public mos_6510_nullary_instruction<0xB8, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.V() = false;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "CLV");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
