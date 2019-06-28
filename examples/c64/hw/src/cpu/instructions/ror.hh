#ifndef CPU_INSTRUCTIONS_ROR_HH
#define CPU_INSTRUCTIONS_ROR_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ror {

static constexpr const char *MNEMONIC = "ROR";

struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x6A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x66;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x76;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x6E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x7E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace ror
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
