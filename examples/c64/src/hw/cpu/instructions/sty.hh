#ifndef CPU_INSTRUCTIONS_STY_HH
#define CPU_INSTRUCTIONS_STY_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sty {

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x84;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x94;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x8C;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace sty
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
