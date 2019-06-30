#ifndef CPU_INSTRUCTIONS_STA_HH
#define CPU_INSTRUCTIONS_STA_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sta {

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x85;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x95;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x8D;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x9D;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x99;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x81;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x91;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace sta
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
