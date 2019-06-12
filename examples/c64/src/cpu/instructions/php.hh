#ifndef CPU_INSTRUCTIONS_PHP_HH
#define CPU_INSTRUCTIONS_PHP_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace php {

struct implied {
	static constexpr const std::uint8_t OPCODE = 0x08;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace php
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
