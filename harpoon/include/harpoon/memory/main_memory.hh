#ifndef HARPOON_MEMORY_MAIN_MEMORY_HH
#define HARPOON_MEMORY_MAIN_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/memory.hh"

#include <list>

namespace harpoon {
namespace memory {

class main_memory : public memory {
public:
	main_memory(const std::string &name = {},
	            const address_range &address_range = {0, address_range::max()})
	    : memory(name, address_range) {}
	main_memory(const main_memory &) = delete;
	main_memory &operator=(const main_memory &) = delete;

	virtual void add_memory(const memory_weak_ptr &memory, bool owner = true);
	virtual void remove_memory(const memory_weak_ptr &memory, bool owner = true);
	virtual void replace_memory(const memory_weak_ptr &old_memory,
	                            const memory_weak_ptr &new_memory, bool owner = true);

	virtual ~main_memory() override;

protected:
	virtual void get_cell(address address, uint8_t &value) override;
	virtual void set_cell(address address, uint8_t value) override;

private:
	memory_ptr get_memory(address address);

	std::list<memory_weak_ptr> _memory;
	memory_weak_ptr _last_used_memory;
	address_range _last_used_range;
};

using main_memory_ptr = std::shared_ptr<main_memory>;
using main_memory_weak_ptr = std::weak_ptr<main_memory>;

template<typename... Args>
main_memory_ptr make_main_memory(Args &&... args) {
	return std::make_shared<main_memory>(std::forward<Args>(args)...);
}

} // namespace memory
} // namespace harpoon

#endif
