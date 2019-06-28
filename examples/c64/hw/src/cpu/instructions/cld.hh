#ifndef CPU_INSTRUCTIONS_CLD_HH
#define CPU_INSTRUCTIONS_CLD_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cld {

static constexpr const char *MNEMONIC = "CLD";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xD8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace cld
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
