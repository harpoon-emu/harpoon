#ifndef HARPOON_MEMORY_CHUNKED_RANDOM_ACCESS_MEMORY_HH
#define HARPOON_MEMORY_CHUNKED_RANDOM_ACCESS_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/chunked_memory.hh"
#include "harpoon/memory/random_access_memory.hh"

namespace harpoon {
namespace memory {

class chunked_random_access_memory : public random_access_memory<chunked_memory> {
public:
	using random_access_memory<chunked_memory>::random_access_memory;

	virtual ~chunked_random_access_memory();
};

using chunked_random_access_memory_ptr = std::shared_ptr<chunked_random_access_memory>;

template<typename... Args>
chunked_random_access_memory_ptr make_chunked_random_access_memory(Args &&... args) {
	return std::make_shared<chunked_random_access_memory>(std::forward<Args>(args)...);
}

} // namespace memory
} // namespace harpoon

#endif
