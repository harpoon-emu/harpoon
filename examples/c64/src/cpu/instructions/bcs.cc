#include "bcs.hh"

#include "../mos_6510.hh"
#include "branch_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace bcs {

harpoon::execution::instruction relative::factory(harpoon::execution::processing_unit *cpu) {
	return relative_branch_factory<&mos_6510::get_flag_C, true>(cpu);
}

} // namespace bcs
} // namespace instructions
} // namespace cpu
} // namespace commodore
