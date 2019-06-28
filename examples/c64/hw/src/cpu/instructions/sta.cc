#include "sta.hh"

#include "../mos_6510.hh"
#include "write_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sta {

template<void (instruction_step::*store)(std::uint8_t)>
using store_a = store_register<std::uint8_t, &mos_6510::get_A, store>;

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_write_factory<store_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_x_write_factory<store_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_write_factory<store_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_x_write_factory<store_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute_y::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_y_write_factory<store_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction indirect_x::factory(harpoon::execution::processing_unit *cpu) {
	return indirect_x_write_factory<store_a>(cpu, MNEMONIC);
}

harpoon::execution::instruction indirect_y::factory(harpoon::execution::processing_unit *cpu) {
	return indirect_y_write_factory<store_a>(cpu, MNEMONIC);
}

} // namespace sta
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
