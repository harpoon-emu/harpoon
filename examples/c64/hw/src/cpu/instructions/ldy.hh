#ifndef CPU_INSTRUCTIONS_LDY_HH
#define CPU_INSTRUCTIONS_LDY_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ldy {

static constexpr const char *MNEMONIC = "LDY";

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xA0;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xA4;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xB4;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xAC;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xBC;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace ldy
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
