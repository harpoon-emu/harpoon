#ifndef HARPOON_MEMORY_EXCEPTION_WRITE_ACCESS_VIOLATION_HH
#define HARPOON_MEMORY_EXCEPTION_WRITE_ACCESS_VIOLATION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/exception/access_violation.hh"

namespace harpoon {
namespace memory {
namespace exception {

class write_access_violation : public access_violation {
public:
	write_access_violation(const std::string &component, address address,
	                       const std::string &file = {}, int line = {},
	                       const std::string &function = {});

	write_access_violation(const write_access_violation &) = default;
	write_access_violation &operator=(const write_access_violation &) = default;

	virtual ~write_access_violation();
};

} // namespace exception
} // namespace memory
} // namespace harpoon

#endif
