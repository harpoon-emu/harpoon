#include "c64.hh"
#include "cpu/mos_6510.hh"
#include "memory/memory.hh"

#include "harpoon/clock/clock.hh"
#include "harpoon/clock/generator/dummy_generator.hh"
#include "harpoon/execution/up_execution_unit.hh"

namespace commodore {

c64::c64(const harpoon::log::log_ptr& log)
	: harpoon::computer_system("Commodore 64") {
	set_log(log);
}

c64::~c64() {}

void c64::create() {
	create_memory();
	create_execution_unit();
}

void c64::create_execution_unit() {
	auto execution_unit = harpoon::execution::make_up_execution_unit("Execution unit");
	set_main_execution_unit(execution_unit);

	auto clock = harpoon::clock::make_clock(
		std::static_pointer_cast<harpoon::clock::generator::generator>(
			harpoon::clock::generator::make_dummy_generator(1000000)), "Clock");
	execution_unit->set_clock(clock);

	auto cpu = std::make_shared<cpu::mos_6510>("CPU");
	execution_unit->set_processing_unit(cpu);

	cpu->add_breakpoint({
		[](harpoon::execution::processing_unit * processing_unit) -> bool {
			cpu::mos_6510 * mos = static_cast<cpu::mos_6510 *>(processing_unit);
			return mos->get_registers().PC == 0xFF61;
		},
		[](harpoon::execution::processing_unit * processing_unit) {
			cpu::mos_6510 * mos = static_cast<cpu::mos_6510 *>(processing_unit);
			mos->get_registers().P.Z() = true;
		}
	});

	cpu->create();
}

void c64::create_memory() {
	auto main_memory = std::make_shared<memory::memory>("Memory", harpoon::memory::address_range{0, 0xffff});
	set_main_memory(main_memory);

	main_memory->create();
}

void c64::prepare() {
	auto execution_unit = std::static_pointer_cast<harpoon::execution::up_execution_unit>(get_main_execution_unit());
	auto cpu = std::static_pointer_cast<cpu::mos_6510>(execution_unit->get_processing_unit());
	cpu->set_memory(get_main_memory());
	harpoon::computer_system::prepare();
}

}
