#ifndef MEMORY_FLAT_MEMORY_HH
#define MEMORY_FLAT_MEMORY_HH

#include "memory.hh"

#include "harpoon/memory/io_memory.hh"
#include "harpoon/memory/main_memory.hh"
#include "harpoon/memory/multiplexed_memory.hh"

namespace c64 {
namespace hw {
namespace memory {

class flat_memory : public memory {
public:
	using memory::memory;

	virtual void create() override;

	virtual void switch_d000_dfff(harpoon::memory::multiplexed_memory::memory_id mem_id) override;

	virtual ~flat_memory() override;
};

} // namespace memory
} // namespace hw
} // namespace c64

#endif
