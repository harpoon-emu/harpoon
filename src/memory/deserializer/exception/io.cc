#include "harpoon/memory/deserializer/exception/io.hh"

#include <iomanip>
#include <sstream>

namespace harpoon {
namespace memory {
namespace deserializer {
namespace exception {

io::io(const std::string &infile, const std::string &file, int line, const std::string &function)
    : harpoon::exception::harpoon_exception("", file, line, function) {
	std::stringstream stream;
	stream << "I/O error. Input file: " << infile;

	set_what(stream.str());
}

io::~io() {}

} // namespace exception
} // namespace deserializer
} // namespace memory
} // namespace harpoon
