#include "compound_memory.hh"

#include "harpoon/memory/chunked_random_access_memory.hh"
#include "harpoon/memory/chunked_read_only_memory.hh"
#include "harpoon/memory/deserializer/binary_file.hh"
#include "harpoon/memory/linear_random_access_memory.hh"
#include "harpoon/memory/linear_read_only_memory.hh"

namespace c64 {
namespace hw {
namespace memory {

compound_memory::~compound_memory() {}

void compound_memory::create() {

	auto read_memory = harpoon::memory::make_main_memory(
	    "Read memory", harpoon::memory::address_range{0x0000, 0xffff});
	auto write_memory = harpoon::memory::make_main_memory(
	    "Write memory", harpoon::memory::address_range{0x0000, 0xffff});

	_read_memory = read_memory;
	_write_memory = write_memory;

	add_component(read_memory);
	add_component(write_memory);

	auto kernal = make_linear_read_only_memory("ROM Kernal",
	                                           harpoon::memory::address_range{0xe000, 0xffff});
	add_component(kernal);
	_kernal_e000_ffff = kernal;
	read_memory->add_memory(_kernal_e000_ffff, false);

	auto basic
	    = make_linear_read_only_memory("ROM BASIC", harpoon::memory::address_range{0xa000, 0xbfff});
	add_component(basic);
	_basic_a000_bfff = basic;
	read_memory->add_memory(_basic_a000_bfff, false);

	auto ram = make_chunked_random_access_memory(
	    "RAM $0100", harpoon::memory::address_range{0x0100, 0x3fff}, 1024);
	add_component(ram);
	_ram_0100_3fff = ram;
	read_memory->add_memory(ram, false);
	write_memory->add_memory(ram, false);

	ram = make_chunked_random_access_memory("RAM $4000",
	                                        harpoon::memory::address_range{0x4000, 0x7fff}, 1024);
	add_component(ram);
	_ram_4000_7fff = ram;
	read_memory->add_memory(ram, false);
	write_memory->add_memory(ram, false);

	ram = make_chunked_random_access_memory("RAM $8000",
	                                        harpoon::memory::address_range{0x8000, 0x9fff}, 1024);
	add_component(ram);
	read_memory->add_memory(ram, false);
	write_memory->add_memory(ram, false);

	ram = make_chunked_random_access_memory("RAM $A000",
	                                        harpoon::memory::address_range{0xa000, 0xbfff}, 1024);
	add_component(ram);
	write_memory->add_memory(ram, false);

	ram = make_chunked_random_access_memory("RAM $C000",
	                                        harpoon::memory::address_range{0xc000, 0xcfff}, 1024);
	add_component(ram);
	read_memory->add_memory(ram, false);
	write_memory->add_memory(ram, false);

	create_d000_dfff_area();

	ram = make_chunked_random_access_memory("RAM $E000",
	                                        harpoon::memory::address_range{0xe000, 0xffff}, 1024);
	add_component(ram);
	write_memory->add_memory(ram, false);
}

void compound_memory::add_read_memory(const harpoon::memory::memory_weak_ptr &memory) {
	_read_memory.lock()->add_memory(memory, false);
}

void compound_memory::add_write_memory(const harpoon::memory::memory_weak_ptr &memory) {
	_write_memory.lock()->add_memory(memory, false);
}

void compound_memory::add_memory(const harpoon::memory::memory_weak_ptr &memory, bool) {
	add_read_memory(memory);
	add_write_memory(memory);
}

void compound_memory::create_d000_dfff_area() {

	auto mplx = harpoon::memory::make_multiplexed_memory(
	    "MPX $D000", harpoon::memory::address_range{0xd000, 0xdfff});
	add_component(mplx);
	_mplx_d000_dfff = mplx;

	auto ram = make_chunked_random_access_memory(
	    "RAM $D000", harpoon::memory::address_range{0xd000, 0xdfff}, 1024);
	add_component(ram);
	_ram_d000_dfff = ram;
	mplx->add_memory(0, ram, false);

	ram = make_chunked_random_access_memory("I/O $D000",
	                                        harpoon::memory::address_range{0xd000, 0xdfff}, 1024);
	add_component(ram);
	_io_d000_dfff = ram;
	mplx->add_memory(5, ram, false);
	mplx->add_memory(6, ram, false);
	mplx->add_memory(7, ram, false);

	auto rom = harpoon::memory::make_chunked_read_only_memory(
	    "ROM $D000", harpoon::memory::address_range{0xd000, 0xdfff}, 1024);
	add_component(rom);
	_character_rom_d000_dfff = rom;
	mplx->add_memory(1, rom, false);
	mplx->add_memory(2, rom, false);
	mplx->add_memory(3, rom, false);

	_read_memory.lock()->add_memory(_mplx_d000_dfff, false);
	_write_memory.lock()->add_memory(_mplx_d000_dfff, false);
}

void compound_memory::prepare() {
	harpoon::memory::main_memory::prepare();

	load_kernal();
	load_basic();
}

void compound_memory::serialize(harpoon::memory::serializer::serializer &serializer) {
	_read_memory.lock()->serialize(serializer);
}

void compound_memory::deserialize(harpoon::memory::deserializer::deserializer &deserializer) {
	_write_memory.lock()->deserialize(deserializer);
}

void compound_memory::load_kernal() {
	harpoon::memory::deserializer::binary_file kernal_bin(
	    _kernal_e000_ffff.lock()->get_address_range().get_start(), "kernal.rom");
	_kernal_e000_ffff.lock()->deserialize(kernal_bin);
}

void compound_memory::load_basic() {
	harpoon::memory::deserializer::binary_file basic_bin(
	    _basic_a000_bfff.lock()->get_address_range().get_start(), "basic.rom");
	_basic_a000_bfff.lock()->deserialize(basic_bin);
}

void compound_memory::get_cell(harpoon::memory::address address, std::uint8_t &value) {
	_read_memory.lock()->get(address, value);
}

void compound_memory::set_cell(harpoon::memory::address address, std::uint8_t value) {
	_write_memory.lock()->set(address, value);
}

void compound_memory::switch_d000_dfff(harpoon::memory::multiplexed_memory::memory_id mem_id) {
	log(component_debug << "Switching $D000-$DFFF to " << mem_id);
	_mplx_d000_dfff.lock()->switch_memory(mem_id);
}

} // namespace memory
} // namespace hw
} // namespace c64
