#ifndef CPU_INSTRUCTIONS_ROL_HH
#define CPU_INSTRUCTIONS_ROL_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rol {

struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x2A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x26;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x36;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x2E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x3E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace rol
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
