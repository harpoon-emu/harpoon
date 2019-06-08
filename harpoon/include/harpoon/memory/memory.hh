#ifndef HARPOON_MEMORY_MEMORY_HH
#define HARPOON_MEMORY_MEMORY_HH

#include "harpoon/harpoon.hh"
#include "harpoon/hardware_component.hh"
#include "harpoon/memory/address_range.hh"

#include <list>

namespace harpoon {
namespace memory {

namespace serializer {
class serializer;
}

class memory;

using memory_ptr = std::shared_ptr<memory>;
using memory_weak_ptr = std::weak_ptr<memory>;

class memory : public hardware_component {
public:

	memory(const std::string& name = {}, const address_range& address_range = {})
		: hardware_component(name), _address_range(address_range) {}

	const address_range& get_address_range() const {
		return _address_range;
	}

	address_range& get_address_range() {
		return _address_range;
	}

	void set_address_range(const address_range& range) {
		_address_range = range;
	}

	bool has_address(address address) const {
		return get_address_range().has_address(address);
	}

	address get_offset(address address) const {
		return get_address_range().get_offset(address);
	}

	virtual void get(address address, std::uint8_t& value) = 0;
	virtual void set(address address, std::uint8_t value) = 0;

	virtual void get(address address, std::uint16_t& value);
	virtual void set(address address, std::uint16_t value);

	virtual void get(address address, std::uint32_t& value);
	virtual void set(address address, std::uint32_t value);

	virtual void get(address address, std::uint64_t& value);
	virtual void set(address address, std::uint64_t value);

	virtual void serialize(serializer::serializer& serializer);
	virtual void deserialize(serializer::serializer& serializer);

	virtual ~memory();

private:
	address_range _address_range{};
};

}
}

#endif

