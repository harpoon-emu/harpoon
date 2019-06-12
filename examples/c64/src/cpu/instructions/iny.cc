#include "iny.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace iny {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return implied_arith_factory<&mos_6510::get_Y, &arith::inc, &mos_6510::set_Y>(cpu);
}

} // namespace iny
} // namespace instructions
} // namespace cpu
} // namespace commodore
