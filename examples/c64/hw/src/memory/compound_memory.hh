#ifndef MEMORY_COMPOUND_MEMORY_HH
#define MEMORY_COMPOUND_MEMORY_HH

#include "memory.hh"

#include "harpoon/memory/io_memory.hh"
#include "harpoon/memory/main_memory.hh"
#include "harpoon/memory/multiplexed_memory.hh"

namespace c64 {
namespace hw {
namespace memory {

class compound_memory : public memory {
public:
	using memory::memory;

	virtual void create() override;

	virtual void serialize(harpoon::memory::serializer::serializer &serializer) override;
	virtual void deserialize(harpoon::memory::deserializer::deserializer &deserializer) override;

	void add_read_memory(const harpoon::memory::memory_weak_ptr &memory);
	void add_write_memory(const harpoon::memory::memory_weak_ptr &memory);
	virtual void add_memory(const harpoon::memory::memory_weak_ptr &memory,
	                        bool owner = true) override;

	virtual void get_cell(harpoon::memory::address address, std::uint8_t &value) override;
	virtual void set_cell(harpoon::memory::address address, std::uint8_t value) override;

	virtual void switch_d000_dfff(harpoon::memory::multiplexed_memory::memory_id mem_id) override;

	virtual ~compound_memory() override;

private:
	void create_d000_dfff_area();

	harpoon::memory::main_memory_weak_ptr _read_memory{};
	harpoon::memory::main_memory_weak_ptr _write_memory{};

	harpoon::memory::memory_weak_ptr _basic_a000_bfff{};
	harpoon::memory::memory_weak_ptr _kernal_e000_ffff{};

	harpoon::memory::memory_weak_ptr _zero_page_0000_00ff{};
	harpoon::memory::memory_weak_ptr _ram_0100_3fff{};
	harpoon::memory::memory_weak_ptr _ram_4000_7fff{};

	harpoon::memory::multiplexed_memory_weak_ptr _mplx_d000_dfff{};
	harpoon::memory::memory_weak_ptr _ram_d000_dfff{};
	harpoon::memory::memory_weak_ptr _character_rom_d000_dfff{};
	harpoon::memory::memory_weak_ptr _io_d000_dfff{};

	harpoon::memory::memory_weak_ptr _ram_e000_ffff{};
};

} // namespace memory
} // namespace hw
} // namespace c64

#endif
