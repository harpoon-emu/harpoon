#ifndef HARPOON_EXECUTION_EXCEPTION_INVALID_INSTRUCTION_HH
#define HARPOON_EXECUTION_EXCEPTION_INVALID_INSTRUCTION_HH

#include "harpoon/harpoon.hh"

#include "harpoon/execution/exception/execution_exception.hh"

namespace harpoon {
namespace execution {
namespace exception {

class invalid_instruction : public execution_exception {
public:
	invalid_instruction(const std::string &component, const std::string &file = {}, int line = {},
	                    const std::string &function = {});

	invalid_instruction(const invalid_instruction &) = default;
	invalid_instruction &operator=(const invalid_instruction &) = default;

	virtual ~invalid_instruction();
};

} // namespace exception
} // namespace execution
} // namespace harpoon

#endif
