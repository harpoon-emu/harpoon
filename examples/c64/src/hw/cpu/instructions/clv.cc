#include "clv.hh"

#include "../mos_6510.hh"
#include "instruction_step.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace clv {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return set_flag_factory<&mos_6510::set_flag_V, false>(cpu);
}

} // namespace clv
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
