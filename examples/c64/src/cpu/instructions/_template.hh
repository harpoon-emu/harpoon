#ifndef CPU_INSTRUCTIONS_XXX_HH
#define CPU_INSTRUCTIONS_XXX_HH

#include "instruction_step.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace family {

struct variant {
	static constexpr const std::uint8_t OPCODE = 0xFF;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace family
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
