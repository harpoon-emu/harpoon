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
	set_range({base, base + static_cast<address>(_input.tellg())});
	_input.seekg(0, _input.beg);
}

void binary_file::do_open_memory_block() {}

std::size_t binary_file::do_read(std::uint8_t *data, std::size_t offset, std::size_t length) {
	_input.seekg(static_cast<std::ifstream::off_type>(get_block_range().get_start()
	                                                  - get_range().get_start() + offset),
	             _input.beg);
	get_block_memory()->log(log_debug_c("binary_file => " + get_block_memory()->get_name())
	                        << "Reading " << length << " bytes from " << _file_name);
	get_block_memory()->log(log_debug_c("binary_file => " + get_block_memory()->get_name())
	                        << "Offset: " << offset << ", file offset: " << _input.tellg());
	_input.read(reinterpret_cast<char *>(data), static_cast<std::streamsize>(length));
	return static_cast<std::size_t>(_input.gcount());
}

} // namespace deserializer
} // namespace memory
} // namespace harpoon
