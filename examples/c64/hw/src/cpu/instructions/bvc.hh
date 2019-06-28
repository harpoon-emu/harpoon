#ifndef CPU_INSTRUCTIONS_BVC_HH
#define CPU_INSTRUCTIONS_BVC_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bvc {

static constexpr const char *MNEMONIC = "BVC";

struct relative {
	static constexpr const std::uint8_t OPCODE = 0x50;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bvc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
