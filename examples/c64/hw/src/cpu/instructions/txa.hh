#ifndef CPU_INSTRUCTIONS_TXA_HH
#define CPU_INSTRUCTIONS_TXA_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace txa {

static constexpr const char *MNEMONIC = "TXA";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x8A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace txa
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
