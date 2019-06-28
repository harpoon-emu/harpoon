#ifndef CPU_INSTRUCTIONS_CLC_HH
#define CPU_INSTRUCTIONS_CLC_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace clc {

static constexpr const char *MNEMONIC = "CLC";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x18;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace clc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
