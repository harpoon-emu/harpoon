#ifndef CPU_INSTRUCTIONS_BNE_HH
#define CPU_INSTRUCTIONS_BNE_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace bne {

struct relative {
	static constexpr const std::uint8_t OPCODE = 0xD0;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bne
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
