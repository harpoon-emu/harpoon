#include "harpoon/memory/main_memory.hh"
#include "harpoon/memory/exception/read_access_violation.hh"
#include "harpoon/memory/exception/write_access_violation.hh"

#include <limits>

namespace harpoon {
namespace memory {

main_memory::~main_memory() {}

void main_memory::add_memory(const memory_weak_ptr& memory, bool owner) {
	if (owner) {
		add_component(memory);
	}
	_memory.push_back(memory);
}

void main_memory::remove_memory(const memory_weak_ptr& memory, bool owner) {
	if (owner) {
		remove_component(memory);
	}
	_memory.remove_if([&memory](const memory_weak_ptr& ptr) {
		return ptr.lock() == memory.lock();
	});
}

void main_memory::replace_memory(const memory_weak_ptr& old_memory,
								 const memory_weak_ptr& new_memory,
								 bool owner) {
	if (!old_memory.expired()) {
		remove_memory(old_memory, owner);
	}
	add_memory(new_memory, owner);
}

memory_ptr main_memory::get_memory(address address) {
	if (!_last_used_memory.expired() && _last_used_range.has_address(address)) {
		return _last_used_memory.lock();
	}

	for (const auto& memory : _memory) {
		const auto& mem_ptr = memory.lock();
		if (mem_ptr->has_address(address)) {
			_last_used_memory = mem_ptr;
			_last_used_range = mem_ptr->get_address_range();
			return mem_ptr;
		}
	}

	return {};
}

void main_memory::get_cell(address address, uint8_t& value) {
	if (!has_address(address)) {
		throw COMPONENT_EXCEPTION(exception::read_access_violation, address);
	}

	auto memory = get_memory(address);
	if (!memory) {
		throw COMPONENT_EXCEPTION(exception::read_access_violation, address);
	}

	memory->get(address, value);
}

void main_memory::set_cell(address address, uint8_t value) {
	if (!has_address(address)) {
		throw COMPONENT_EXCEPTION(exception::write_access_violation, address);
	}

	auto memory = get_memory(address);
	if (!memory) {
		throw COMPONENT_EXCEPTION(exception::write_access_violation, address);
	}

	memory->set(address, value);
}

}
}
