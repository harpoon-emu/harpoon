#ifndef CPU_INSTRUCTIONS_TSX_HH
#define CPU_INSTRUCTIONS_TSX_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace tsx {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xBA;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace tsx
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
