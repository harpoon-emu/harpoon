#ifndef HARPOON_MEMORY_LINEAR_MEMORY_HH
#define HARPOON_MEMORY_LINEAR_MEMORY_HH

#include "harpoon/harpoon.hh"
#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {

class linear_memory : public memory {
public:

	linear_memory(const std::string& name = {}, const address_range& address_range = {})
		: memory(name, address_range) {}
	linear_memory(const linear_memory&) = delete;
	linear_memory& operator=(const linear_memory&) = delete;

	virtual void prepare();
	virtual void cleanup();

	virtual void get(address address, uint8_t& value);
	virtual void set(address address, uint8_t value);

	virtual void serialize(serializer::serializer& serializer);
	virtual void deserialize(serializer::serializer& serializer);

	virtual ~linear_memory();

private:
	std::unique_ptr<std::uint8_t[]> _memory{};
};

}
}

#endif

