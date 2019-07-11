#ifndef HARPOON_MEMORY_DESERIALIZER_EXCEPTION_BAD_BLOCK_RANGE_HH
#define HARPOON_MEMORY_DESERIALIZER_EXCEPTION_BAD_BLOCK_RANGE_HH

#include "harpoon/harpoon.hh"

#include "harpoon/exception/harpoon_exception.hh"
#include "harpoon/memory/address_range.hh"

namespace harpoon {
namespace memory {
namespace deserializer {
namespace exception {

class bad_block_range : public harpoon::exception::harpoon_exception {
public:
	bad_block_range(const address_range &block_range, const address_range &range,
	                const std::string &file = {}, int line = {}, const std::string &function = {});
	bad_block_range(const bad_block_range &) = default;
	bad_block_range &operator=(const bad_block_range &) = default;

	virtual ~bad_block_range();
};

} // namespace exception
} // namespace deserializer
} // namespace memory
} // namespace harpoon

#endif
