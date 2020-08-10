#ifndef HARPOON_MEMORY_CHUNKED_READ_ONLY_MEMORY_HH
#define HARPOON_MEMORY_CHUNKED_READ_ONLY_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/chunked_memory.hh"
#include "harpoon/memory/read_only_memory.hh"

namespace harpoon {
namespace memory {

class chunked_read_only_memory : public read_only_memory<chunked_memory> {
public:
	using read_only_memory<chunked_memory>::read_only_memory;

	virtual ~chunked_read_only_memory();
};

using chunked_read_only_memory_ptr = std::shared_ptr<chunked_read_only_memory>;

template<typename... Args>
chunked_read_only_memory_ptr make_chunked_read_only_memory(Args &&... args) {
	return std::make_shared<chunked_read_only_memory>(std::forward<Args>(args)...);
}

} // namespace memory
} // namespace harpoon

#endif
