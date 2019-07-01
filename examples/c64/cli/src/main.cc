#include "c64.hh"
#include "console_log.hh"

#include <boost/program_options.hpp>
#include <iostream>

int main(int argc, char **argv) {

	try {
		boost::program_options::options_description desc("Allowed options");

		desc.add_options()("help,h", "produce help message");
		desc.add_options()("disassemble,d", "disassemble executed instructions");

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

		c64->create();

		if (vm.count("disassemble")) {
			c64->get_main_execution_unit()->enable_disassemble();
		}

		c64->prepare();
		c64->boot();
		c64->run();

	} catch (std::exception &e) {
		std::cerr << "error: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "unknown exception" << std::endl;
	}
}
