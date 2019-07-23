#ifndef HARPOON_MEMORY_SERIALIZER_BINARY_FILE_HH
#define HARPOON_MEMORY_SERIALIZER_BINARY_FILE_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/serializer/serializer.hh"

#include <fstream>

namespace harpoon {
namespace memory {
namespace serializer {

class binary_file : public serializer {
public:
	binary_file(const address_range &range, const std::string &file_name);

protected:
	virtual void do_start_memory_block() override;
	virtual std::size_t do_write(uint8_t *data, std::size_t offset, std::size_t length,
	                             bool sparse) override;

private:
	std::string _file_name{};
	std::ofstream _output{};
};

} // namespace serializer
} // namespace memory
} // namespace harpoon

#endif
