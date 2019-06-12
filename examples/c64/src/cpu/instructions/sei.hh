#ifndef CPU_INSTRUCTIONS_SEI_HH
#define CPU_INSTRUCTIONS_SEI_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace sei {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x78;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace sei
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
