#include "brk.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace brk {

template<std::uint16_t address, void (mos_6510::*set_reg)(std::uint8_t v)>
class set_pc : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		std::uint8_t v;
		get_cpu()->get_memory()->get(address, v);
		(get_cpu()->*set_reg)(v);
	}
};

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<fetch_program_code>(), make_instruction_step<internal_read>(),
	          make_instruction_step<stack_push<&mos_6510::get_PCH>>(),
	          make_instruction_step<stack_push<&mos_6510::get_PCL>>(),
	          make_instruction_step<stack_push<&mos_6510::get_P>>(),
	          make_instruction_step<set_pc<0xFFFE, &mos_6510::set_PCL>>(),
	          make_instruction_step<set_pc<0xFFFF, &mos_6510::set_PCH>>()});
}

} // namespace brk
} // namespace instructions
} // namespace cpu
} // namespace commodore
