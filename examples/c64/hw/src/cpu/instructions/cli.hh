#ifndef CPU_INSTRUCTIONS_CLI_HH
#define CPU_INSTRUCTIONS_CLI_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cli {

static constexpr const char *MNEMONIC = "CLI";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x58;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace cli
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
