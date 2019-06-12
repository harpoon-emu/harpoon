#ifndef CPU_INSTRUCTIONS_TXS_HH
#define CPU_INSTRUCTIONS_TXS_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace txs {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x9A;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace txs
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
