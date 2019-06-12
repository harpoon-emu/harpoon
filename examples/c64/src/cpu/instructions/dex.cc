#include "dex.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace dex {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return implied_arith_factory<&mos_6510::get_X, &arith::dec, &mos_6510::set_X>(cpu);
}

} // namespace dex
} // namespace instructions
} // namespace cpu
} // namespace commodore
