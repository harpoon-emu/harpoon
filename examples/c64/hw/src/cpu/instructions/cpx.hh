#ifndef CPU_INSTRUCTIONS_CPX_HH
#define CPU_INSTRUCTIONS_CPX_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cpx {

static constexpr const char *MNEMONIC = "CPX";

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xE0;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xE4;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xEC;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace cpx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
