#ifndef CPU_INSTRUCTIONS_CLV_HH
#define CPU_INSTRUCTIONS_CLV_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace clv {

static constexpr const char *MNEMONIC = "CLV";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xB8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace clv
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
