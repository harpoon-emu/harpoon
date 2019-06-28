#include "bit.hh"

#include "../mos_6510.hh"
#include "arith_instruction.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bit {

template<void (instruction_step::*fetch)(std::uint8_t &, bool)>
using arith_bit = accumulator_arith<&arith::bit, fetch>;

harpoon::execution::instruction zero_page::factory(harpoon::execution::processing_unit *cpu) {
	return zero_page_read_factory<arith_bit>(cpu, MNEMONIC);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return absolute_read_factory<arith_bit>(cpu, MNEMONIC);
}

} // namespace bit
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
