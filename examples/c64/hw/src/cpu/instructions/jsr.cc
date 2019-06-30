#include "jsr.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace jsr {

class set_pc : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

void set_pc::execute() {
	get_cpu()->internal_read_program_code();
	get_cpu()->set_PC(get_cpu()->get_internal_memory_access().w);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu,
	    {make_instruction_step<fetch_program_code>(), make_instruction_step<internal_read>(),
	     make_instruction_step<stack_push<&mos_6510::get_PCH>>(),
	     make_instruction_step<stack_push<&mos_6510::get_PCL>>(), make_instruction_step<set_pc>()});
}

} // namespace jsr
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
