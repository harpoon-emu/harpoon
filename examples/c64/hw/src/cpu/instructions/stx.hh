#ifndef CPU_INSTRUCTIONS_STX_HH
#define CPU_INSTRUCTIONS_STX_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace stx {

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x86;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_y {
	static constexpr const std::uint8_t OPCODE = 0x96;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x8E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace stx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
