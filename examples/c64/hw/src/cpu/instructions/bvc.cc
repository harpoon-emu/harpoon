#include "bvc.hh"

#include "../mos_6510.hh"
#include "branch_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bvc {

harpoon::execution::instruction relative::factory(harpoon::execution::processing_unit *cpu) {
	return relative_branch_factory<&mos_6510::get_flag_V, false>(cpu, MNEMONIC);
}

} // namespace bvc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
