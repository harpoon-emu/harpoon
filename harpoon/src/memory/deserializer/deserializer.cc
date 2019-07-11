#include "harpoon/memory/deserializer/deserializer.hh"

#include "harpoon/memory/deserializer/exception/bad_block_range.hh"

namespace harpoon {
namespace memory {
namespace deserializer {

deserializer::~deserializer() {}

address_range deserializer::has_range(const address_range &range) {
	return _range.get_intersection(range);
}

std::size_t deserializer::read(const memory *memory, uint8_t *data, const address_range &range) {
	return do_read(memory, data, range);
}

} // namespace deserializer
} // namespace memory
} // namespace harpoon
