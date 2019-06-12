#ifndef CPU_INSTRUCTIONS_JSR_HH
#define CPU_INSTRUCTIONS_JSR_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace jsr {

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x20;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace jsr
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
