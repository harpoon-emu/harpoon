#ifndef HARPOON_MEMORY_DESERIALIZER_BINARY_FILE_HH
#define HARPOON_MEMORY_DESERIALIZER_BINARY_FILE_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/deserializer/deserializer.hh"

#include <fstream>

namespace harpoon {
namespace memory {
namespace deserializer {

class binary_file : public deserializer {
public:
	binary_file(address base, const std::string &file_name);

protected:
	virtual std::size_t do_read(const memory *memory, uint8_t *data, const address_range &range);

private:
	std::string _file_name{};
	std::ifstream _input{};
};

} // namespace deserializer
} // namespace memory
} // namespace harpoon

#endif
