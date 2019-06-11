#ifndef CPU_INSTRUCTIONS_PHP_HH
#define CPU_INSTRUCTIONS_PHP_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class php : public mos_6510_nullary_instruction<0x08, 3> {
public:
	void execute() {
		push(static_cast<std::uint8_t>(get_cpu()->get_registers().P.get_flags()));
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "PHP");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
