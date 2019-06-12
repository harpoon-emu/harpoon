#ifndef CPU_INSTRUCTIONS_DEY_HH
#define CPU_INSTRUCTIONS_DEY_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace dey {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x88;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace dey
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
