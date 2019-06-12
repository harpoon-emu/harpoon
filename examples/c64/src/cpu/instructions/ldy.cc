#include "ldy.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace ldy {

template<void (instruction_step::*fetch)(std::uint8_t &, bool)>
using load_y = load_register<std::uint8_t, &mos_6510::set_Y, fetch, true>;

harpoon::execution::instruction immediate::factory(harpoon::execution::processing_unit *cpu) {
	return immediate_read_factory<load_y>(cpu);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_read_factory<load_y>(cpu);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_index_read_factory<load_y, &mos_6510::get_X>(cpu);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_read_factory<load_y>(cpu);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_index_read_factory<load_y, &mos_6510::get_X>(cpu);
}

} // namespace ldy
} // namespace instructions
} // namespace cpu
} // namespace commodore
