#ifndef HARPOON_MEMORY_DESERIALIZER_DESERIALIZER_HH
#define HARPOON_MEMORY_DESERIALIZER_DESERIALIZER_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/address_range.hh"
#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {
namespace deserializer {

class deserializer {
public:
	deserializer(const address_range &range) : _range(range) {}

	const address_range &get_range() const {
		return _range;
	}

	virtual void open_memory_block(const memory *memory);
	virtual void open_memory_block(const memory *memory, const address_range &range);

	virtual std::size_t read(uint8_t *data, std::size_t length);
	virtual std::size_t read(uint8_t *data, std::size_t offset, std::size_t length);

	virtual void close_memory_block();

	virtual ~deserializer();

protected:
	void set_range(const address_range &range) {
		_range = range;
	}

	const memory *get_block_memory() const {
		return _block_memory;
	}

	const address_range &get_block_range() const {
		return _block_range;
	}

	virtual void do_open_memory_block() = 0;
	virtual std::size_t do_read(uint8_t *data, std::size_t offset, std::size_t length) = 0;
	virtual void do_close_memory_block();

private:
	address_range _range{};
	const memory *_block_memory{};
	address_range _block_range{};
};

} // namespace deserializer
} // namespace memory
} // namespace harpoon

#endif
