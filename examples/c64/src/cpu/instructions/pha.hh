#ifndef CPU_INSTRUCTIONS_PHA_HH
#define CPU_INSTRUCTIONS_PHA_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace pha {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x48;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace pha
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
