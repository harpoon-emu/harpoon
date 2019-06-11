#ifndef HARPOON_EXECUTION_INSTRUCTION_HH
#define HARPOON_EXECUTION_INSTRUCTION_HH

#include "harpoon/harpoon.hh"

#include <functional>

namespace harpoon {
namespace execution {

class processing_unit;

using instruction_handler = std::function<std::uint_fast64_t(processing_unit *)>;
using disassemble_handler = std::function<void(std::ostream &)>;

template<typename CPU>
class instruction {
public:
	static constexpr const std::uint_fast64_t CYCLES_DECODE = 0;
	static constexpr const std::uint_fast64_t CYCLES_EXECUTE = 0;
	static constexpr const std::uint32_t OPCODE = 0x00;
	static constexpr const std::size_t LENGTH = 0;

	void decode() {}
	void execute() {}
	void disassemble(std::ostream &) const {}

	void set_cpu(CPU *cpu) {
		_cpu = cpu;
	}

protected:
	CPU *get_cpu() const {
		return _cpu;
	}

private:
	CPU *_cpu{};
};

} // namespace execution
} // namespace harpoon

#endif
