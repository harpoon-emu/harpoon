#ifndef MEMORY_MEMORY_HH
#define MEMORY_MEMORY_HH

#include "harpoon/memory/main_memory.hh"
#include "harpoon/memory/multiplexed_memory.hh"
#include "harpoon/memory/io_memory.hh"

namespace commodore {
namespace memory {

class memory : public harpoon::memory::main_memory {
public:

	using harpoon::memory::main_memory::main_memory;

	void create();

	virtual void prepare() override;

	virtual void shutdown() override;

	void add_read_memory(const harpoon::memory::memory_weak_ptr& memory);
	void add_write_memory(const harpoon::memory::memory_weak_ptr& memory);
	void add_memory(const harpoon::memory::memory_weak_ptr& memory);

	virtual void get_cell(harpoon::memory::address address, std::uint8_t& value) override;
	virtual void set_cell(harpoon::memory::address address, std::uint8_t value) override;

	void switch_d000_dfff(harpoon::memory::multiplexed_memory::memory_id mem_id);

	virtual ~memory() override;

private:

	void load_kernal();
	void load_basic();

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

using memory_ptr = std::shared_ptr<memory>;
using memory_weak_ptr = std::weak_ptr<memory>;

}
}

#endif

