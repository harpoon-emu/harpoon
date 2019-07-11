#include "harpoon/memory/deserializer/binary_file.hh"

#include "harpoon/memory/deserializer/exception/io.hh"
#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {
namespace deserializer {

binary_file::binary_file(address base, const std::string &file_name)
    : deserializer({base, base}), _file_name(file_name) {
	_input.exceptions(std::ifstream::badbit);
	_input.open(_file_name, std::ios::binary);

	if (!_input.good()) {
		throw HARPOON_EXCEPTION(exception::io, file_name);
	}

	_input.seekg(0, _input.end);
	set_range({base, base + static_cast<address>(_input.tellg()) - 1});
	_input.seekg(0, _input.beg);
}

std::size_t binary_file::do_read(const memory *memory, std::uint8_t *data,
                                 const address_range &range) {
	address_range r = has_range(range);
	if (!r) {
		return 0;
	}

	_input.seekg(static_cast<std::ifstream::off_type>(range.get_start() - get_range().get_start()),
	             _input.beg);
	memory->log(log_debug_c(_file_name + " => " + memory->get_name())
	            << "Reading " << r.get_length() << " bytes into " << r);
	_input.read(reinterpret_cast<char *>(data + r.get_start() - range.get_start()),
	            static_cast<std::streamsize>(r.get_length()));
	return static_cast<std::size_t>(_input.gcount());
}

} // namespace deserializer
} // namespace memory
} // namespace harpoon
