#ifndef CPU_INSTRUCTIONS_BRK_HH
#define CPU_INSTRUCTIONS_BRK_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace brk {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x00;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace brk
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
