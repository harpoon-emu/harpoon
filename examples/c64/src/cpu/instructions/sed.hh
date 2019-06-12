#ifndef CPU_INSTRUCTIONS_SED_HH
#define CPU_INSTRUCTIONS_SED_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace sed {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xF8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace sed
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
