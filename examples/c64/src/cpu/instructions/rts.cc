#include "rts.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "instruction_step.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace rts {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<internal_read>(),
	             make_instruction_step<internal_read>(),
	             make_instruction_step<stack_pull<&mos_6510::set_PCL, false>>(),
	             make_instruction_step<stack_pull<&mos_6510::set_PCH, false>>(),
	             make_instruction_step<
	                 implied_arith16<&mos_6510::get_PC, &arith::inc, &mos_6510::set_PC, false>>(),
	         });
}

} // namespace rts
} // namespace instructions
} // namespace cpu
} // namespace commodore
