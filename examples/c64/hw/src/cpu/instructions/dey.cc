#include "dey.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace dey {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return implied_arith_factory<&mos_6510::get_Y, &arith::dec, &mos_6510::set_Y>(cpu);
}

} // namespace dey
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
