#ifndef MEMORY_MEMORY_HH
#define MEMORY_MEMORY_HH

#include "harpoon/memory/main_memory.hh"
#include "harpoon/memory/multiplexed_memory.hh"

namespace c64 {
namespace hw {
namespace memory {

class memory : public harpoon::memory::main_memory {
public:
	using harpoon::memory::main_memory::main_memory;

	virtual void create() = 0;

	virtual void switch_d000_dfff(harpoon::memory::multiplexed_memory::memory_id mem_id) = 0;

	virtual ~memory() override;

private:
};

using memory_ptr = std::shared_ptr<memory>;
using memory_weak_ptr = std::weak_ptr<memory>;

} // namespace memory
} // namespace hw
} // namespace c64

#endif
