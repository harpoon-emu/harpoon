#ifndef CPU_INSTRUCTIONS_LDX_HH
#define CPU_INSTRUCTIONS_LDX_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ldx {

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xA2;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xA6;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_y {
	static constexpr const std::uint8_t OPCODE = 0xB6;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xAE;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xBE;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace ldx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
