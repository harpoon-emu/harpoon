#include "and.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace and_ {

template<void (instruction_step::*fetch)(std::uint8_t &, bool)>
using arith_and = accumulator_arith<&arith::and_, fetch>;

harpoon::execution::instruction immediate::factory(harpoon::execution::processing_unit *cpu) {
	return immediate_read_factory<arith_and>(cpu);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_read_factory<arith_and>(cpu);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_index_read_factory<arith_and, &mos_6510::get_X>(cpu);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_read_factory<arith_and>(cpu);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_index_read_factory<arith_and, &mos_6510::get_X>(cpu);
}

harpoon::execution::instruction absolute_y::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_index_read_factory<arith_and, &mos_6510::get_Y>(cpu);
}

harpoon::execution::instruction indirect_x::factory(harpoon::execution::processing_unit *cpu) {
	return indirect_x_read_factory<arith_and>(cpu);
}

harpoon::execution::instruction indirect_y::factory(harpoon::execution::processing_unit *cpu) {
	return indirect_y_read_factory<arith_and>(cpu);
}

} // namespace and_
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
