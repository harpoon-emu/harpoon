#include "flat_memory.hh"

#include "harpoon/memory/chunked_random_access_memory.hh"
#include "harpoon/memory/chunked_read_only_memory.hh"
#include "harpoon/memory/linear_random_access_memory.hh"
#include "harpoon/memory/linear_read_only_memory.hh"
#include "harpoon/memory/serializer/binary_file.hh"

namespace c64 {
namespace hw {
namespace memory {

flat_memory::~flat_memory() {}

void flat_memory::create() {
	auto ram = make_chunked_random_access_memory(
	    "RAM $0000", harpoon::memory::address_range{0x0000, 0xffff}, 1024);
	add_memory(ram);
}

void flat_memory::switch_d000_dfff(harpoon::memory::multiplexed_memory::memory_id) {}

} // namespace memory
} // namespace hw
} // namespace c64
