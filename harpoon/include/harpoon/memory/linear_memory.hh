#ifndef HARPOON_MEMORY_LINEAR_MEMORY_HH
#define HARPOON_MEMORY_LINEAR_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/memory.hh"

namespace harpoon {
namespace memory {

class linear_memory : public memory {
public:
	linear_memory(const std::string &name = {}, const address_range &address_range = {})
	    : memory(name, address_range) {}
	linear_memory(const linear_memory &) = delete;
	linear_memory &operator=(const linear_memory &) = delete;

	virtual void prepare() override;
	virtual void cleanup() override;

	virtual void serialize(serializer::serializer &serializer) override;
	virtual void deserialize(serializer::serializer &serializer) override;

	virtual ~linear_memory() override;

protected:
	virtual void get_cell(address address, uint8_t &value) override;
	virtual void set_cell(address address, uint8_t value) override;

private:
	std::unique_ptr<std::uint8_t[]> _memory{};
};

} // namespace memory
} // namespace harpoon

#endif
