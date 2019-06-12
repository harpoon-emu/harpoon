#include "nop.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "instruction_step.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace nop {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<internal_read>(), make_instruction_step<internal_read>()});
}

} // namespace nop
} // namespace instructions
} // namespace cpu
} // namespace commodore
