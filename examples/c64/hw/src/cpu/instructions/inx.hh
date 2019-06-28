#ifndef CPU_INSTRUCTIONS_INX_HH
#define CPU_INSTRUCTIONS_INX_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace inx {

static constexpr const char *MNEMONIC = "INX";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xE8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace inx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
