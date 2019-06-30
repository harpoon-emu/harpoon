#include "bmi.hh"

#include "../mos_6510.hh"
#include "branch_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bmi {

harpoon::execution::instruction relative::factory(harpoon::execution::processing_unit *cpu) {
	return relative_branch_factory<&mos_6510::get_flag_N, true>(cpu);
}

} // namespace bmi
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
