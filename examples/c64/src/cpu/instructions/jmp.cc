#include "jmp.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace jmp {

class set_pc : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

void set_pc::execute() {
	get_cpu()->internal_read_program_code();
	get_cpu()->set_PC(get_cpu()->get_internal_memory_access().w);
}

class fetch_pcl : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

void fetch_pcl::execute() {
	std::uint8_t v;
	get_cpu()->get_memory()->get(get_cpu()->get_internal_memory_access().w, v);
	get_cpu()->set_latch(v);
}

class fetch_pch : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

void fetch_pch::execute() {
	std::uint8_t v;
	std::uint16_t a = static_cast<std::uint16_t>(get_cpu()->get_internal_memory_access().b.h << 8)
	                  | static_cast<std::uint8_t>(get_cpu()->get_internal_memory_access().b.l + 1);
	get_cpu()->get_memory()->get(a, v);
	get_cpu()->set_PCL(get_cpu()->get_latch());
	get_cpu()->set_PCH(v);
}

harpoon::execution::instruction absolute::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<fetch_program_code>(), make_instruction_step<set_pc>()});
}

harpoon::execution::instruction indirect::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(cpu, {make_instruction_step<fetch_program_code>(),
	                                             make_instruction_step<fetch_program_code>(),
	                                             make_instruction_step<fetch_pcl>(),
	                                             make_instruction_step<fetch_pch>()});
}

} // namespace jmp
} // namespace instructions
} // namespace cpu
} // namespace commodore
