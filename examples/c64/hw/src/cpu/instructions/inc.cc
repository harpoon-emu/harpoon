#include "inc.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace inc {

template<void (instruction_step::*store)(std::uint8_t)>
using arith_inc = rmw_arith<&arith::inc, store>;

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_modify_factory<arith_inc>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_x_modify_factory<arith_inc>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_modify_factory<arith_inc>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_x_modify_factory<arith_inc>(cpu, MNEMONIC);
}

} // namespace inc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
