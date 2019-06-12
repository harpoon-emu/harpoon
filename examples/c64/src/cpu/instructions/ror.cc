#include "ror.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace ror {

template<void (instruction_step::*store)(std::uint8_t)>
using arith_ror = rmw_arith<&arith::ror, store>;

harpoon::execution::instruction accumulator::factory(harpoon::execution::processing_unit *cpu) {
	return accumulator_arith_factory<&arith::ror>(cpu);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_modify_factory<arith_ror>(cpu);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_index_modify_factory<arith_ror, &mos_6510::get_X>(cpu);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_modify_factory<arith_ror>(cpu);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_index_modify_factory<arith_ror, &mos_6510::get_X>(cpu);
}

} // namespace ror
} // namespace instructions
} // namespace cpu
} // namespace commodore
