#include "harpoon/execution/exception/invalid_instruction.hh"

namespace harpoon {
namespace execution {
namespace exception {

invalid_instruction::invalid_instruction(const std::string &component, const std::string &file,
                                         int line, const std::string &function)
    : execution_exception(component, "invalid instruction", file, line, function) {}

invalid_instruction::~invalid_instruction() {}

} // namespace exception
} // namespace execution
} // namespace harpoon
