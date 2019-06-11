#ifndef CPU_INSTRUCTIONS_CLI_HH
#define CPU_INSTRUCTIONS_CLI_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class cli : public mos_6510_nullary_instruction<0x58, 2> {
public:
	void execute() {
		get_cpu()->get_registers().P.I() = false;
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "CLI");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
