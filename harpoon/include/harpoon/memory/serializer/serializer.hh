#ifndef HARPOON_MEMORY_SERIALIZER_SERIALIZER_HH
#define HARPOON_MEMORY_SERIALIZER_SERIALIZER_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/address_range.hh"
#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {
namespace serializer {

class serializer {
public:
	virtual void start_memory_block(const memory *memory, const address_range &range) = 0;
	virtual std::size_t write(const uint8_t *data, std::size_t length, bool sparse = false) = 0;
	virtual void end_memory_block() = 0;

	virtual void seek_memory_block(const memory *memory, const address_range &range) = 0;
	virtual std::size_t read(uint8_t *data, std::size_t length) = 0;

	virtual ~serializer();
};

} // namespace serializer
} // namespace memory
} // namespace harpoon

#endif
