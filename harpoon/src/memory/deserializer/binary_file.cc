#include "harpoon/memory/deserializer/binary_file.hh"

#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {
namespace deserializer {

binary_file::binary_file(const address_range &range, const std::string &file_name)
    : deserializer(range), _file_name(file_name) {
	_input.exceptions(std::ifstream::badbit);
	_input.open(_file_name, std::ios::binary);
}

void binary_file::do_open_memory_block() {}

std::size_t binary_file::do_read(std::uint8_t *data, std::size_t offset, std::size_t length) {
	_input.seekg(static_cast<std::ifstream::off_type>(get_block_range().get_start()
	                                                  - get_range().get_start() + offset),
	             _input.beg);
	get_block_memory()->log(log_debug_c("binary_file => " + get_block_memory()->get_name())
	                        << "Reading " << length << " bytes from " << _file_name);
	_input.read(reinterpret_cast<char *>(data), static_cast<std::streamsize>(length));
	return static_cast<std::size_t>(_input.gcount());
}

} // namespace deserializer
} // namespace memory
} // namespace harpoon
