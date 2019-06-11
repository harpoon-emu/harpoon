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
	binary_file(const std::string &file_name) : _file_name(file_name) {}

	virtual void start_memory_block(const memory *memory, const address_range &range);
	virtual std::size_t write(const uint8_t *data, std::size_t length, bool sparse = false);
	virtual void end_memory_block();

	virtual void seek_memory_block(const memory *memory, const address_range &range);
	virtual std::size_t read(uint8_t *data, std::size_t length);

private:
	address_range _address_range{};
	const memory *_memory{};
	std::string _file_name{};
	std::ifstream _input{};
	std::ofstream _output{};
};

} // namespace serializer
} // namespace memory
} // namespace harpoon

#endif
