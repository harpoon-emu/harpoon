#ifndef HARPOON_MEMORY_LINEAR_READ_ONLY_MEMORY_HH
#define HARPOON_MEMORY_LINEAR_READ_ONLY_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/linear_memory.hh"
#include "harpoon/memory/read_only_memory.hh"

namespace harpoon {
namespace memory {

class linear_read_only_memory : public read_only_memory<linear_memory> {
public:
	using read_only_memory<linear_memory>::read_only_memory;

	virtual ~linear_read_only_memory();
};

using linear_read_only_memory_ptr = std::shared_ptr<linear_read_only_memory>;

template<typename... Args>
linear_read_only_memory_ptr make_linear_read_only_memory(Args &&... args) {
	return std::make_shared<linear_read_only_memory>(std::forward<Args>(args)...);
}

} // namespace memory
} // namespace harpoon

#endif
