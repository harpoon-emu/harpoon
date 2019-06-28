#include "iny.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace iny {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return implied_arith_factory<&mos_6510::get_Y, &arith::inc, &mos_6510::set_Y>(cpu, MNEMONIC);
}

} // namespace iny
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
