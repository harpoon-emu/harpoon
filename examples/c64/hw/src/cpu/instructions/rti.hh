#ifndef CPU_INSTRUCTIONS_RTI_HH
#define CPU_INSTRUCTIONS_RTI_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rti {

static constexpr const char *MNEMONIC = "RTI";

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x40;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace rti
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
