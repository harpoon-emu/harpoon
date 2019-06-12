#ifndef CPU_INSTRUCTIONS_BEQ_HH
#define CPU_INSTRUCTIONS_BEQ_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace beq {

struct relative {
	static constexpr const std::uint8_t OPCODE = 0xF0;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace beq
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
