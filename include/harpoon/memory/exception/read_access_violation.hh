#ifndef HARPOON_MEMORY_EXCEPTION_READ_ACCESS_VIOLATION_HH
#define HARPOON_MEMORY_EXCEPTION_READ_ACCESS_VIOLATION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/exception/access_violation.hh"

namespace harpoon {
namespace memory {
namespace exception {

class read_access_violation : public access_violation {
public:
	read_access_violation(const std::string &component, address address,
	                      const std::string &file = {}, int line = {},
	                      const std::string &function = {});

	read_access_violation(const read_access_violation &) = default;
	read_access_violation &operator=(const read_access_violation &) = default;

	virtual ~read_access_violation();
};

} // namespace exception
} // namespace memory
} // namespace harpoon

#endif
