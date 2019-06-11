#ifndef HARPOON_EXECUTION_INSTRUCTION_INVOKER_HH
#define HARPOON_EXECUTION_INSTRUCTION_INVOKER_HH

#include "harpoon/harpoon.hh"

namespace harpoon {
namespace execution {

class processing_unit;

template<typename T>
class instruction_invoker {
public:
	instruction_invoker(T &instruction) : _instruction(instruction) {}
	instruction_invoker(const instruction_invoker<T> &) = default;
	instruction_invoker<T> &operator=(const instruction_invoker<T> &) = default;

	std::uint_fast64_t operator()(processing_unit *) {
		_instruction.execute();
		return T::CYCLES_EXECUTE;
	}

private:
	T _instruction;
};

} // namespace execution
} // namespace harpoon

#endif
