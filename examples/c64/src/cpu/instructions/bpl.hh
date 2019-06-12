#ifndef CPU_INSTRUCTIONS_BPL_HH
#define CPU_INSTRUCTIONS_BPL_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace bpl {

struct relative {
	static constexpr const std::uint8_t OPCODE = 0x10;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bpl
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
