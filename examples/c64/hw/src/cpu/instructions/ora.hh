#ifndef CPU_INSTRUCTIONS_ORA_HH
#define CPU_INSTRUCTIONS_ORA_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ora {

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0x09;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x05;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x15;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x0D;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x1D;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x19;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x01;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x11;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace ora
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
