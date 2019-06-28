#include "sty.hh"

#include "../mos_6510.hh"
#include "write_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sty {

template<void (instruction_step::*store)(std::uint8_t)>
using store_y = store_register<std::uint8_t, &mos_6510::get_Y, store>;

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_write_factory<store_y>(cpu, MNEMONIC);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_x_write_factory<store_y>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_write_factory<store_y>(cpu, MNEMONIC);
}

} // namespace sty
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
