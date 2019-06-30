#include "cpy.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cpy {

template<void (instruction_step::*load)(std::uint8_t &, bool)>
using compare_y = compare_register<&mos_6510::get_Y, load>;

harpoon::execution::instruction immediate::factory(harpoon::execution::processing_unit *cpu) {
	return immediate_read_factory<compare_y>(cpu);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_read_factory<compare_y>(cpu);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_read_factory<compare_y>(cpu);
}

} // namespace cpy
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
