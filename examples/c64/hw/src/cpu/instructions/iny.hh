#ifndef CPU_INSTRUCTIONS_INY_HH
#define CPU_INSTRUCTIONS_INY_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace iny {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xC8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace iny
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
