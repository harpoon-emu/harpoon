#ifndef CPU_INSTRUCTIONS_TYA_HH
#define CPU_INSTRUCTIONS_TYA_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace tya {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x98;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace tya
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
