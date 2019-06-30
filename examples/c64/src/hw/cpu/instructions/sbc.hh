#ifndef CPU_INSTRUCTIONS_SBC_HH
#define CPU_INSTRUCTIONS_SBC_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sbc {

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xE9;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xE5;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xF5;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xED;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xFD;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xF9;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0xE1;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0xF1;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace sbc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
