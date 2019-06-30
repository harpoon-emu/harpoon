#ifndef CPU_INSTRUCTIONS_DEC_HH
#define CPU_INSTRUCTIONS_DEC_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace dec {

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xC6;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xD6;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xCE;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xDE;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace dec
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
