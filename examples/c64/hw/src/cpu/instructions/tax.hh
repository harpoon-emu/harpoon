#ifndef CPU_INSTRUCTIONS_TAX_HH
#define CPU_INSTRUCTIONS_TAX_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tax {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xAA;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace tax
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
