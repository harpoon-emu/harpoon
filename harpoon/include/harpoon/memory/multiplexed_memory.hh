#ifndef HARPOON_MEMORY_MULTIPLEXED_MEMORY_HH
#define HARPOON_MEMORY_MULTIPLEXED_MEMORY_HH

#include "harpoon/harpoon.hh"
#include "harpoon/memory/memory.hh"

#include <map>

namespace harpoon {
namespace memory {

class multiplexed_memory : public memory {
public:

    using memory_id = unsigned int;

	multiplexed_memory(const std::string& name = {}, const address_range& address_range = {0, address_range::max()})
		: memory(name, address_range) {}
	multiplexed_memory(const multiplexed_memory&) = delete;
	multiplexed_memory& operator=(const multiplexed_memory&) = delete;

	void add_memory(memory_id mem_id, const memory_weak_ptr& memory, bool owner = true);
	void remove_memory(memory_id mem_id, bool owner = true);
	void replace_memory(memory_id mem_id, const memory_weak_ptr& new_memory, bool owner = true);

    void switch_memory(memory_id mem_id);

	virtual void get(address address, uint8_t& value);
	virtual void set(address address, uint8_t value);

	virtual ~multiplexed_memory();

private:
	std::map<memory_id, memory_weak_ptr> _memory{};
	memory_ptr _active_memory{};
};

using multiplexed_memory_ptr = std::shared_ptr<multiplexed_memory>;
using multiplexed_memory_weak_ptr = std::weak_ptr<multiplexed_memory>;

template<typename... Args>
multiplexed_memory_ptr make_multiplexed_memory(Args&&... args) {
	return std::make_shared<multiplexed_memory>(std::forward<Args>(args)...);
}

}
}

#endif

