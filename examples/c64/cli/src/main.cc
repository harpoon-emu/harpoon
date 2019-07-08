#include "c64.hh"
#include "console_log.hh"
#include "cpu/mos_6510.hh"
#include "integer.hh"

#include <boost/program_options.hpp>
#include <iostream>

static void set_options_description(boost::program_options::options_description &desc) {
	desc.add_options()("help,h", "produce help message");
	desc.add_options()("disassemble,d", boost::program_options::bool_switch()->default_value(false),
	                   "disassemble executed instructions");
	desc.add_options()("flat-memory,f", boost::program_options::bool_switch()->default_value(false),
	                   "use flat memory (no ROM, no I/O, don't load KERNAL and ROM)");
	desc.add_options()(
	    "init-pc,p",
	    boost::program_options::value<c64::cli::integer<std::uint16_t>>()->default_value(0xffff),
	    "initial value of PC register ($FFFF - read from RESET_VECTOR)");
}

int main(int argc, char **argv) {

	try {
		boost::program_options::options_description desc("Allowed options");
		set_options_description(desc);

		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc),
		                              vm);
		boost::program_options::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 0;
		}

		std::shared_ptr<c64::cli::console_log> log;
		std::shared_ptr<c64::hw::c64> c64;

		log = std::make_shared<c64::cli::console_log>();
		c64 = std::make_shared<c64::hw::c64>(log);

		if (vm["flat-memory"].as<bool>()) {
			c64->enable_flat_memory();
		}

		c64->create();
		auto mos_6510 = c64->get_mos_6510();

		if (vm["disassemble"].as<bool>()) {
			c64->get_main_execution_unit()->enable_disassemble();
		}
		mos_6510->set_init_PC(vm["init-pc"].as<c64::cli::integer<std::uint16_t>>());

		c64->prepare();
		c64->boot();
		c64->run();
	} catch (std::exception &e) {
		std::cerr << "error: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "unknown exception" << std::endl;
	}
}
