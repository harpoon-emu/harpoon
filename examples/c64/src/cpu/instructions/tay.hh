#ifndef CPU_INSTRUCTIONS_TAY_HH
#define CPU_INSTRUCTIONS_TAY_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace tay {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xA8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace tay
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
