#include "harpoon/memory/linear_memory.hh"
#include "harpoon/memory/serializer/serializer.hh"
#include "harpoon/memory/exception/memory_exception.hh"
#include "harpoon/memory/exception/read_access_violation.hh"
#include "harpoon/memory/exception/write_access_violation.hh"

#include <limits>

namespace harpoon {
namespace memory {

linear_memory::~linear_memory() {}

void linear_memory::prepare() {

	auto len = get_address_range().get_length();
	if (0 == len) {
		throw COMPONENT_EXCEPTION(exception::memory_exception, "Zero-length memory block.");
	}

	log(component_notice << "Allocating " << len << " bytes memory block");
	_memory.reset(new uint8_t[static_cast<size_t>(len)]);

	memory::prepare();
}

void linear_memory::cleanup() {
	memory::cleanup();
	log(component_notice << "Freeing memory");
	_memory.reset();
}

void linear_memory::get_cell(address address, uint8_t& value) {
	if (!has_address(address)) {
		throw COMPONENT_EXCEPTION(exception::read_access_violation, address);
	}

	/*
	 * It's safe to cast. Linear block can't be larger than max(size_t), 
	 * otherwise prepare() will fail.
	 */
	size_t offset = static_cast<size_t>(address - get_address_range().get_start());
	value = _memory[offset];
}

void linear_memory::set_cell(address address, uint8_t value) {
	if (!has_address(address)) {
		throw COMPONENT_EXCEPTION(exception::write_access_violation, address);
	}

	/*
	 * It's safe to cast. Linear block can't be larger than max(size_t),
	 * otherwise prepare() will fail.
	 */
	size_t offset = static_cast<size_t>(address - get_address_range().get_start());
	_memory[offset] = value;
}

void linear_memory::serialize(serializer::serializer& serializer) {
	serializer.start_memory_block(this, get_address_range());
	serializer.write(_memory.get(), static_cast<std::size_t>(get_address_range().get_length()));
	serializer.end_memory_block();
}

void linear_memory::deserialize(serializer::serializer& serializer) {
	serializer.seek_memory_block(this, get_address_range());
	serializer.read(_memory.get(), static_cast<std::size_t>(get_address_range().get_length()));
}

}
}
