#include "_template.hh"

#include "../mos_6510.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace family {

class step_1 : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

void step_1::execute() {
	get_cpu()->get_program_code(get_cpu()->get_registers().X);
}

harpoon::execution::instruction variant::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(cpu, {make_instruction_step<step_1>()});
}

} // namespace family
} // namespace instructions
} // namespace cpu
} // namespace commodore
