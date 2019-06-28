#include "plp.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace plp {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<internal_read>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<stack_pull<&mos_6510::set_P, false>>(),
	    },
	    disassembler::implied(MNEMONIC));
}

} // namespace plp
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
