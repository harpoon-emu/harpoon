#ifndef CPU_INSTRUCTIONS_ASL_HH
#define CPU_INSTRUCTIONS_ASL_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace asl {

static constexpr const char *MNEMONIC = "ASL";

struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x0A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x06;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x16;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x0E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x1E;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace asl
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
