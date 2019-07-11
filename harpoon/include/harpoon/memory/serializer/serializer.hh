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
	serializer(const address_range &range) : _range(range) {}

	virtual void start_memory_block(const memory *memory);
	virtual void start_memory_block(const memory *memory, const address_range &range);

	virtual std::size_t write(uint8_t *data, std::size_t length, bool sparse = false);
	virtual std::size_t write(uint8_t *data, std::size_t offset, std::size_t length,
	                          bool sparse = false);

	virtual void finalize_memory_block();

	virtual ~serializer();

protected:
	const address_range &get_range() const {
		return _range;
	}

	const memory *get_block_memory() const {
		return _block_memory;
	}

	const address_range &get_block_range() const {
		return _block_range;
	}

	virtual void do_start_memory_block() = 0;
	virtual std::size_t do_write(uint8_t *data, std::size_t offset, std::size_t length, bool sparse)
	    = 0;
	virtual void do_finalize_memory_block();

private:
	address_range _range{};
	const memory *_block_memory{};
	address_range _block_range{};
};

} // namespace serializer
} // namespace memory
} // namespace harpoon

#endif
