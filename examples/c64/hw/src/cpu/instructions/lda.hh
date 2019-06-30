#ifndef CPU_INSTRUCTIONS_LDA_HH
#define CPU_INSTRUCTIONS_LDA_HH

#include "harpoon/execution/instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace lda {

struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xA9;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xA5;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xB5;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xAD;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xBD;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xB9;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0xA1;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0xB1;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace lda
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
