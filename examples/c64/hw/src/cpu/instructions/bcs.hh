#ifndef CPU_INSTRUCTIONS_BCS_HH
#define CPU_INSTRUCTIONS_BCS_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bcs {

static constexpr const char *MNEMONIC = "BCS";

struct relative {
	static constexpr const std::uint8_t OPCODE = 0xB0;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bcs
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
