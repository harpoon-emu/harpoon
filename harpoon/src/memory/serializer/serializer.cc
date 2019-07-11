#include "harpoon/memory/serializer/serializer.hh"

#include "harpoon/memory/serializer/exception/bad_block_range.hh"

namespace harpoon {
namespace memory {
namespace serializer {

serializer::~serializer() {}

void serializer::start_memory_block(const memory *memory) {
	start_memory_block(memory, memory->get_address_range());
}

void serializer::start_memory_block(const memory *block_memory, const address_range &block_range) {
	if (block_range.get_start() < _range.get_start() || block_range.get_end() > _range.get_end()) {
		throw HARPOON_EXCEPTION(exception::bad_block_range, block_range, _range);
	}

	_block_memory = block_memory;
	_block_range = block_range;
}

std::size_t serializer::write(uint8_t *data, std::size_t length, bool sparse) {
	return write(data, 0, length, sparse);
}

std::size_t serializer::write(uint8_t *data, std::size_t offset, std::size_t length, bool sparse) {
	return do_write(data, offset, length, sparse);
}

void serializer::finalize_memory_block() {
	do_finalize_memory_block();
}

void serializer::do_finalize_memory_block() {}

} // namespace serializer
} // namespace memory
} // namespace harpoon
