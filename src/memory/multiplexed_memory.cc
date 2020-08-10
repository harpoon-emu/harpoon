#include "harpoon/memory/multiplexed_memory.hh"

#include "harpoon/memory/exception/multiplexer_error.hh"
#include "harpoon/memory/exception/read_access_violation.hh"
#include "harpoon/memory/exception/write_access_violation.hh"

#include <limits>

namespace harpoon {
namespace memory {

multiplexed_memory::~multiplexed_memory() {}

void multiplexed_memory::add_memory(memory_id mem_id, const memory_ptr &memory, bool owner) {
	remove_memory(mem_id, owner);
	if (owner) {
		add_component(memory);
	}
	_memory[mem_id] = memory;
}

void multiplexed_memory::remove_memory(memory_id mem_id, bool owner) {
	if (_memory.find(mem_id) == _memory.end()) {
		return;
	}

	const auto &memory = _memory[mem_id];

	if (owner) {
		remove_component(memory);
	}
	_memory.erase(mem_id);

	if (_active_memory == memory) {
		_active_memory.reset();
	}
}

void multiplexed_memory::replace_memory(memory_id mem_id, const memory_ptr &new_memory,
                                        bool owner) {
	remove_memory(mem_id, owner);
	add_memory(mem_id, new_memory, owner);
}

void multiplexed_memory::switch_memory(memory_id mem_id) {
	if (_memory.find(mem_id) == _memory.end()) {
		throw COMPONENT_EXCEPTION(exception::multiplexer_error, mem_id);
	}
	_active_memory = _memory[mem_id];
}

void multiplexed_memory::get_cell(address address, uint8_t &value) {
	if (_active_memory.get() == nullptr) {
		throw COMPONENT_EXCEPTION(exception::multiplexer_error, ~0U);
	}
	_active_memory->get(address, value);
}

void multiplexed_memory::set_cell(address address, uint8_t value) {
	if (_active_memory.get() == nullptr) {
		throw COMPONENT_EXCEPTION(exception::multiplexer_error, ~0U);
	}
	_active_memory->get(address, value);
}

} // namespace memory
} // namespace harpoon
