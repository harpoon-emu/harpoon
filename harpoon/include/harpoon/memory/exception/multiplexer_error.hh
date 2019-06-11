#ifndef HARPOON_MEMORY_EXCEPTION_MULTIPLEXER_ERROR_HH
#define HARPOON_MEMORY_EXCEPTION_MULTIPLEXER_ERROR_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/exception/memory_exception.hh"

namespace harpoon {
namespace memory {
namespace exception {

class multiplexer_error : public memory_exception {
public:
	multiplexer_error(const std::string &component, unsigned int mem_id,
	                  const std::string &file = {}, int line = {},
	                  const std::string &function = {});

	multiplexer_error(const multiplexer_error &) = default;
	multiplexer_error &operator=(const multiplexer_error &) = default;

	virtual ~multiplexer_error();
};

} // namespace exception
} // namespace memory
} // namespace harpoon

#endif
