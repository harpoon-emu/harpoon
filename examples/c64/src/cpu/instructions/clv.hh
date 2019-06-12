#ifndef CPU_INSTRUCTIONS_CLV_HH
#define CPU_INSTRUCTIONS_CLV_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace clv {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0xB8;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace clv
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
