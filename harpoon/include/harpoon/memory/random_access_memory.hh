#ifndef HARPOON_MEMORY_RANDOM_ACCESS_MEMORY_HH
#define HARPOON_MEMORY_RANDOM_ACCESS_MEMORY_HH

#include "harpoon/harpoon.hh"

namespace harpoon {
namespace memory {

template<typename MemoryImplementation>
class random_access_memory : public MemoryImplementation {
public:
	using MemoryImplementation::MemoryImplementation;

	virtual ~random_access_memory() {}
};

template<typename MemoryImplementation>
using random_access_memory_ptr = std::shared_ptr<random_access_memory<MemoryImplementation>>;

template<typename MemoryImplementation>
using random_access_memory_weak_ptr = std::weak_ptr<random_access_memory<MemoryImplementation>>;

template<typename MemoryImplementation, typename... Args>
random_access_memory_ptr<MemoryImplementation> make_random_access_memory(Args &&... args) {
	return std::make_shared<random_access_memory<MemoryImplementation>>(
	    std::forward<Args>(args)...);
}

} // namespace memory
} // namespace harpoon

#endif
