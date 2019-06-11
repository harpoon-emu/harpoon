#ifndef CPU_INSTRUCTIONS_RTI_HH
#define CPU_INSTRUCTIONS_RTI_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class rti : public mos_6510_nullary_instruction<0x40, 6> {
public:
	void execute() {
		std::uint8_t flags{};
		pop(flags);
		get_cpu()->get_registers().P.set_flags(flags);
		pop(get_cpu()->get_registers().PC);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "RTI");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
