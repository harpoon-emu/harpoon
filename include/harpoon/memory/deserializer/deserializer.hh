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

	virtual address_range has_range(const address_range &range);
	virtual std::size_t read(const memory *memory, uint8_t *data, const address_range &range);

	virtual ~deserializer();

protected:
	void set_range(const address_range &range) {
		_range = range;
	}

	virtual std::size_t do_read(const memory *memory, uint8_t *data, const address_range &range) = 0;

private:
	address_range _range{};
};

} // namespace deserializer
} // namespace memory
} // namespace harpoon

#endif
