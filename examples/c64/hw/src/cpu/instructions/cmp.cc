#include "cmp.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cmp {

template<void (instruction_step::*load)(std::uint8_t &, bool)>
using compare_a = compare_register<&mos_6510::get_A, load>;

harpoon::execution::instruction immediate::factory(harpoon::execution::processing_unit *cpu) {
	return immediate_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_x_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_x_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute_y::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_y_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction indirect_x::factory(harpoon::execution::processing_unit *cpu) {
	return indirect_x_read_factory<compare_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction indirect_y::factory(harpoon::execution::processing_unit *cpu) {
	return indirect_y_read_factory<compare_a>(cpu, MNEMONIC);
}

} // namespace cmp
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
