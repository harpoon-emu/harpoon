#ifndef CPU_INSTRUCTIONS_CLI_HH
#define CPU_INSTRUCTIONS_CLI_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace cli {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x58;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace cli
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
