#ifndef CPU_INSTRUCTIONS_PLP_HH
#define CPU_INSTRUCTIONS_PLP_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace plp {

static constexpr const char *MNEMONIC = "PLP";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x28;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace plp
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
