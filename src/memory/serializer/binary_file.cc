#include "harpoon/memory/serializer/binary_file.hh"

#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {
namespace serializer {

binary_file::binary_file(const address_range &range, const std::string &file_name)
    : serializer(range), _file_name(file_name) {
	_output.exceptions(std::ofstream::badbit);
	_output.open(_file_name, std::ios::binary | std::ios::trunc);
}

void binary_file::do_start_memory_block() {}

std::size_t binary_file::do_write(uint8_t *data, std::size_t offset, std::size_t length,
                                  bool sparse) {
	_output.seekp(static_cast<std::ifstream::off_type>(get_block_range().get_start()
	                                                   - get_range().get_start() + offset),
	              _output.beg);
	if (sparse) {
		get_block_memory()->log(log_debug_c(get_block_memory()->get_name() + " => binary_file")
		                        << "Writing " << length << " bytes of sparse buffer to "
		                        << _file_name);
		_output.seekp(static_cast<std::ifstream::off_type>(length), _output.cur);
	} else {
		get_block_memory()->log(log_debug_c(get_block_memory()->get_name() + " => binary_file")
		                        << "Writing " << length << " bytes to " << _file_name);
		_output.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(length));
	}
	return length;
}

} // namespace serializer
} // namespace memory
} // namespace harpoon
