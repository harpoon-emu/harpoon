#ifndef CPU_INSTRUCTIONS_DEX_HH
#define CPU_INSTRUCTIONS_DEX_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace dex {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xCA;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace dex
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
