#ifndef CPU_INSTRUCTIONS_BMI_HH
#define CPU_INSTRUCTIONS_BMI_HH

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace bmi {

struct relative {
	static constexpr const std::uint8_t OPCODE = 0x30;
	static harpoon::execution::instruction factory(harpoon::execution::processing_unit *cpu);
};

} // namespace bmi
} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
