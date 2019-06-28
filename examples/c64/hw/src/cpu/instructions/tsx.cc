#include "tsx.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tsx {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return transfer_register_factory<std::uint8_t, &mos_6510::get_SP, &mos_6510::set_X, true>(
	    cpu, MNEMONIC);
}

} // namespace tsx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
