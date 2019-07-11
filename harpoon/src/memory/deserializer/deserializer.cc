#include "harpoon/memory/deserializer/deserializer.hh"

#include "harpoon/memory/deserializer/exception/bad_block_range.hh"

namespace harpoon {
namespace memory {
namespace deserializer {

deserializer::~deserializer() {}

void deserializer::open_memory_block(const memory *memory) {
	open_memory_block(memory, memory->get_address_range());
}

void deserializer::open_memory_block(const memory *block_memory, const address_range &block_range) {

	if (block_range.get_start() < _range.get_start() || block_range.get_end() > _range.get_end()) {
		throw HARPOON_EXCEPTION(exception::bad_block_range, block_range, _range);
	}

	_block_memory = block_memory;
	_block_range = block_range;
}

std::size_t deserializer::read(uint8_t *data, std::size_t length) {
	return read(data, 0, length);
}

std::size_t deserializer::read(uint8_t *data, std::size_t offset, std::size_t length) {
	return do_read(data, offset, length);
}

void deserializer::close_memory_block() {
	do_close_memory_block();
}

void deserializer::do_close_memory_block() {}

} // namespace deserializer
} // namespace memory
} // namespace harpoon
