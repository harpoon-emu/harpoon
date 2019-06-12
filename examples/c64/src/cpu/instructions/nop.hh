#ifndef CPU_INSTRUCTIONS_NOP_HH
#define CPU_INSTRUCTIONS_NOP_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace nop {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xEA;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace nop
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
