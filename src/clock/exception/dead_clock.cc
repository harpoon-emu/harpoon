#include "harpoon/clock/exception/dead_clock.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace clock {
namespace exception {

dead_clock::dead_clock(const std::string &component, harpoon::clock::cycle cycle,
                       const std::string &file, int line, const std::string &function)
    : clock_exception(component, "", file, line, function), _cycle(cycle) {
	std::stringstream stream;
	stream << "Dead clock detected at cycle " << cycle;
	set_what(stream.str());
}

dead_clock::~dead_clock() {}

} // namespace exception
} // namespace clock
} // namespace harpoon
