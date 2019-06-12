#ifndef CPU_INSTRUCTIONS_TXA_HH
#define CPU_INSTRUCTIONS_TXA_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace txa {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x8A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace txa
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
