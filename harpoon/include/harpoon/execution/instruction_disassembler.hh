#ifndef HARPOON_EXECUTION_INSTRUCTION_DISASSEMBLER_HH
#define HARPOON_EXECUTION_INSTRUCTION_DISASSEMBLER_HH

#include "harpoon/harpoon.hh"

namespace harpoon {
namespace execution {

class processing_unit;

template<typename T>
class instruction_disassembler {
public:
	instruction_disassembler(T &instruction) : _instruction(instruction) {}
	instruction_disassembler(const instruction_disassembler<T> &) = default;
	instruction_disassembler<T> &operator=(const instruction_disassembler<T> &) = default;

	void operator()(std::ostream &stream) {
		_instruction.disassemble(stream);
	}

private:
	T _instruction;
};

} // namespace execution
} // namespace harpoon

#endif
