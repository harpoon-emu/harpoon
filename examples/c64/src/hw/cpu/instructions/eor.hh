#ifndef CPU_INSTRUCTIONS_EOR_HH
#define CPU_INSTRUCTIONS_EOR_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace eor {

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0x49;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x45;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x55;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x4D;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x5D;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x59;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x41;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x51;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace eor
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
