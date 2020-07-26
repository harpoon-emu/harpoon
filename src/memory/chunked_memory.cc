#include "harpoon/memory/chunked_memory.hh"

#include "harpoon/memory/deserializer/deserializer.hh"
#include "harpoon/memory/exception/memory_exception.hh"
#include "harpoon/memory/exception/read_access_violation.hh"
#include "harpoon/memory/exception/write_access_violation.hh"
#include "harpoon/memory/serializer/serializer.hh"

namespace harpoon {
namespace memory {

chunked_memory::~chunked_memory() {}

void chunked_memory::prepare() {
	auto len = get_address_range().get_length();

	if (0 == len) {
		throw COMPONENT_EXCEPTION(exception::memory_exception, "Zero-length memory block.");
	}
	if (0 == _chunk_length) {
		throw COMPONENT_EXCEPTION(exception::memory_exception, "Invalid chunk length (0).");
	}

	chunk_container::size_type chunks
	    = static_cast<chunk_container::size_type>(len / _chunk_length);
	if (0 < len % _chunk_length) {
		chunks++;
	}

	log(component_notice << "Chunking " << len << " bytes of memory into " << chunks
	                     << " chunks of " << _chunk_length << " bytes each");
	_memory.resize(chunks);

	memory::prepare();
}

void chunked_memory::cleanup() {
	memory::cleanup();
	log(component_notice << "Freeing memory");
	_memory.clear();
}

void chunked_memory::get_cell(address address, uint8_t &value) {
	if (!has_address(address)) {
		throw COMPONENT_EXCEPTION(exception::read_access_violation, address);
	}

	const chunk_ptr &chunk = get_chunk(address);
	if (chunk) {
		chunk_offset offset = get_chunk_offset(address);
		value = chunk.get()[offset];
	}
}

void chunked_memory::set_cell(address address, uint8_t value) {
	if (!has_address(address)) {
		throw COMPONENT_EXCEPTION(exception::write_access_violation, address);
	}

	chunk_ptr &chunk = get_chunk(address);
	if (!chunk) {
		allocate_chunk(chunk, address);
	}

	chunk_offset offset = get_chunk_offset(address);
	chunk.get()[offset] = value;
}

inline void chunked_memory::allocate_chunk(chunk_ptr &chunk, address address) {
	log(component_debug << "Allocating chunk #" << get_chunk_index(address));
	chunk.reset(new uint8_t[_chunk_length], std::default_delete<chunk_item[]>());
}

void chunked_memory::serialize(serializer::serializer &serializer) {
	serializer.start_memory_block(this);
	for (address address = get_address_range().get_start(); address < get_address_range().get_end();
	     address += _chunk_length) {
		chunk_ptr &chunk = get_chunk(address);
		serializer.write(chunk.get(), address - get_address_range().get_start(), _chunk_length,
		                 !chunk);
	}
	serializer.finalize_memory_block();
}

void chunked_memory::deserialize(deserializer::deserializer &deserializer) {
	for (address address = get_address_range().get_start(); address < get_address_range().get_end();
	     address += _chunk_length) {

		address_range cr{address, address + _chunk_length - 1};
		cr.intersect(get_address_range());
		cr.intersect(deserializer.get_range());
		if (cr.is_empty()) {
			continue;
		}

		chunk_ptr &chunk = get_chunk(address);
		if (!chunk) {
			allocate_chunk(chunk, address);
		}

		deserializer.read(this, chunk.get() + get_chunk_offset(cr.get_start()), cr);
	}
}

} // namespace memory
} // namespace harpoon
