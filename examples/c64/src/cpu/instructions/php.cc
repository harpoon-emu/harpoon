#include "php.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace php {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(cpu,
	                                       {make_instruction_step<internal_read>(),
	                                        make_instruction_step<stack_push<&mos_6510::get_P>>()});
}

} // namespace php
} // namespace instructions
} // namespace cpu
} // namespace commodore
