#ifndef CPU_INSTRUCTIONS_RTS_HH
#define CPU_INSTRUCTIONS_RTS_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rts {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x60;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace rts
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
