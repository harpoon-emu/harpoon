#include "harpoon/memory/memory.hh"

#include "harpoon/memory/deserializer/deserializer.hh"
#include "harpoon/memory/serializer/serializer.hh"

namespace harpoon {
namespace memory {

memory::~memory() {}

void memory::get(address address, std::uint8_t &value) {
	get_cell(address, value);
}

void memory::set(address address, std::uint8_t value) {
	set_cell(address, value);
}

void memory::get(address address, std::uint16_t &value) {
	std::uint8_t lo, hi;
	get(address, lo);
	get(address + 1, hi);
	value = ((static_cast<std::uint16_t>(hi << 8)) | lo);
}

void memory::set(address address, std::uint16_t value) {
	set(address, static_cast<std::uint8_t>(value & 0xff));
	set(address + 1, static_cast<std::uint8_t>((value >> 8) & 0xff));
}

void memory::get(address address, std::uint32_t &value) {
	std::uint16_t lo, hi;
	get(address, lo);
	get(address + 2, hi);
	value = ((static_cast<std::uint32_t>(hi) << 16) | lo);
}

void memory::set(address address, std::uint32_t value) {
	set(address, static_cast<std::uint16_t>(value & 0xffff));
	set(address + 2, static_cast<std::uint16_t>((value >> 16) & 0xffff));
}

void memory::get(address address, std::uint64_t &value) {
	std::uint32_t lo, hi;
	get(address, lo);
	get(address + 4, hi);
	value = ((static_cast<std::uint64_t>(hi) << 32) | lo);
}

void memory::set(address address, std::uint64_t value) {
	set(address, static_cast<std::uint32_t>(value & 0xffffffff));
	set(address + 4, static_cast<std::uint32_t>((value >> 32) & 0xffffffff));
}

void memory::serialize(serializer::serializer &) {}

void memory::deserialize(deserializer::deserializer &) {}

} // namespace memory
} // namespace harpoon
