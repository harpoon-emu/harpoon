#include "ldx.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ldx {

template<void (instruction_step::*fetch)(std::uint8_t &, bool)>
using load_x = load_register<std::uint8_t, &mos_6510::set_X, fetch, true>;

harpoon::execution::instruction immediate::factory(harpoon::execution::processing_unit *cpu) {
	return immediate_read_factory<load_x>(cpu);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_read_factory<load_x>(cpu);
}

harpoon::execution::instruction zero_page_y::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_index_read_factory<load_x, &mos_6510::get_Y>(cpu);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_read_factory<load_x>(cpu);
}

harpoon::execution::instruction absolute_y::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_index_read_factory<load_x, &mos_6510::get_Y>(cpu);
}

} // namespace ldx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
