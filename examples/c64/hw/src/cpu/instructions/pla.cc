#include "pla.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace pla {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<internal_read>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<stack_pull<&mos_6510::set_A, true>>(),
	    },
	    disassembler::implied(MNEMONIC));
}

} // namespace pla
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
