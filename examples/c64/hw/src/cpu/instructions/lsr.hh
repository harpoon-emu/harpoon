#ifndef CPU_INSTRUCTIONS_LSR_HH
#define CPU_INSTRUCTIONS_LSR_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace lsr {

static constexpr const char *MNEMONIC = "LSR";

struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x4A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x46;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x56;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x4E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x5E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace lsr
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
