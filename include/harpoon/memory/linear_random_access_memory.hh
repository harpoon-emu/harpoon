#ifndef HARPOON_MEMORY_LINEAR_RANDOM_ACCESS_MEMORY_HH
#define HARPOON_MEMORY_LINEAR_RANDOM_ACCESS_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/linear_memory.hh"
#include "harpoon/memory/random_access_memory.hh"

namespace harpoon {
namespace memory {

class linear_random_access_memory : public random_access_memory<linear_memory> {
public:
	using random_access_memory<linear_memory>::random_access_memory;

	virtual ~linear_random_access_memory();
};

using linear_random_access_memory_ptr = std::shared_ptr<linear_random_access_memory>;

template<typename... Args>
linear_random_access_memory_ptr make_linear_random_access_memory(Args &&... args) {
	return std::make_shared<linear_random_access_memory>(std::forward<Args>(args)...);
}

} // namespace memory
} // namespace harpoon

#endif
