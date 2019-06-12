#ifndef CPU_INSTRUCTIONS_BCS_HH
#define CPU_INSTRUCTIONS_BCS_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace bcs {

struct relative {
	static constexpr const std::uint8_t OPCODE = 0xB0;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bcs
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
