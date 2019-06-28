#ifndef HARPOON_EXECUTION_INSTRUCTION_HH
#define HARPOON_EXECUTION_INSTRUCTION_HH

#include "harpoon/harpoon.hh"

#include <functional>
#include <vector>

namespace harpoon {
namespace execution {

class processing_unit;

class instruction {
public:
	using step_handler = std::function<std::uint32_t(const instruction &)>;
	using disassemble_handler = std::function<void(const instruction &, std::ostream &)>;

	using step_handlers = std::pair<step_handler, step_handler>;

	instruction() {}
	instruction(processing_unit *processing_unit, std::vector<step_handlers> &&steps, const disassemble_handler& d_hndl)
	    : _processing_unit{processing_unit}, _step_handlers{steps}, _disassemble_handler(d_hndl), _step{0} {}

	std::uint32_t step() {
		auto delay = _step_handlers[_step].first(*this);
		if (delay == 0) {
			delay = _step_handlers[_step].second(*this);
			_step++;
		}
		return delay;
	}

	void disassemble(std::ostream &s) {
		if (_disassemble_handler) {
			_disassemble_handler(*this, s);
		}
	}

	bool done() const {
		return _step == _step_handlers.size();
	}

	processing_unit *get_processing_unit() const {
		return _processing_unit;
	}

	std::uint32_t get_step() const {
		return _step;
	}

private:
	processing_unit *_processing_unit{};
	std::vector<step_handlers> _step_handlers{};
	disassemble_handler _disassemble_handler{};
	std::uint32_t _step{};
};

} // namespace execution
} // namespace harpoon

#endif
