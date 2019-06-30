#include <boost/program_options.hpp>
#include <iostream>

int main(int argc, char **argv) {

	try {
		boost::program_options::options_description desc("Allowed options");

		desc.add_options()("help,h", "produce help message");

		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc),
		                              vm);
		boost::program_options::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
		}

	} catch (std::exception &e) {
		std::cerr << "error: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "unknown exception" << std::endl;
	}
}
