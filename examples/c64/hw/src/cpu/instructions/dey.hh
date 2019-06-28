#ifndef CPU_INSTRUCTIONS_DEY_HH
#define CPU_INSTRUCTIONS_DEY_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace dey {

static constexpr const char *MNEMONIC = "DEY";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x88;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace dey
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
