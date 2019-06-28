#ifndef CPU_INSTRUCTIONS_BIT_HH
#define CPU_INSTRUCTIONS_BIT_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bit {

static constexpr const char *MNEMONIC = "BIT";

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x24;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x2C;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bit
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
