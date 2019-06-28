#ifndef CPU_INSTRUCTIONS_BCC_HH
#define CPU_INSTRUCTIONS_BCC_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bcc {

static constexpr const char *MNEMONIC = "BCC";

struct relative {
	static constexpr const std::uint8_t OPCODE = 0x90;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bcc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
