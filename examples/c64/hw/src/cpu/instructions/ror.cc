#include "ror.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ror {

template<void (instruction_step::*store)(std::uint8_t)>
using arith_ror = rmw_arith<&arith::ror, store>;

harpoon::execution::instruction accumulator::factory(harpoon::execution::processing_unit *cpu) {
	return accumulator_arith_factory<&arith::ror>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_modify_factory<arith_ror>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_x_modify_factory<arith_ror>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_modify_factory<arith_ror>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_x_modify_factory<arith_ror>(cpu, MNEMONIC);
}

} // namespace ror
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
