#ifndef CPU_INSTRUCTIONS_RTI_HH
#define CPU_INSTRUCTIONS_RTI_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace rti {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x40;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace rti
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
