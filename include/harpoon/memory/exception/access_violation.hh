#ifndef HARPOON_MEMORY_EXCEPTION_ACCESS_VIOLATION_HH
#define HARPOON_MEMORY_EXCEPTION_ACCESS_VIOLATION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/address.hh"
#include "harpoon/memory/exception/memory_exception.hh"

namespace harpoon {
namespace memory {
namespace exception {

class access_violation : public memory_exception {
public:
	access_violation(const std::string &component, address address, const std::string &file = {},
	                 int line = {}, const std::string &function = {});

	access_violation(const access_violation &) = default;
	access_violation &operator=(const access_violation &) = default;

	address get_address() const {
		return _address;
	}

	virtual ~access_violation();

private:
	address _address{};
};

} // namespace exception
} // namespace memory
} // namespace harpoon

#endif
