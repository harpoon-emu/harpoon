#include "rol.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rol {

template<void (instruction_step::*store)(std::uint8_t)>
using arith_rol = rmw_arith<&arith::rol, store>;

harpoon::execution::instruction accumulator::factory(harpoon::execution::processing_unit *cpu) {
	return accumulator_arith_factory<&arith::rol>(cpu);
}

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_modify_factory<arith_rol>(cpu);
}

harpoon::execution::instruction zero_page_x::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_index_modify_factory<arith_rol, &mos_6510::get_X>(cpu);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_modify_factory<arith_rol>(cpu);
}

harpoon::execution::instruction absolute_x::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_index_modify_factory<arith_rol, &mos_6510::get_X>(cpu);
}

} // namespace rol
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
