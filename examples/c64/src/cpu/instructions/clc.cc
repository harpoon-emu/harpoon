#include "clc.hh"

#include "../mos_6510.hh"
#include "instruction_step.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace clc {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return set_flag_factory<&mos_6510::set_flag_C, false>(cpu);
}

} // namespace clc
} // namespace instructions
} // namespace cpu
} // namespace commodore
