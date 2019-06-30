#ifndef CPU_INSTRUCTIONS_INC_HH
#define CPU_INSTRUCTIONS_INC_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace inc {

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xE6;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xF6;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xEE;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xFE;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace inc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
