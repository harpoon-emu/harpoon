#ifndef HARPOON_EXECUTION_PROCESSING_UNIT_HH
#define HARPOON_EXECUTION_PROCESSING_UNIT_HH

#include "harpoon/harpoon.hh"

#include "harpoon/execution/breakpoint.hh"
#include "harpoon/execution/execution_unit.hh"
#include "harpoon/execution/instruction.hh"
#include "harpoon/hardware_component.hh"

#include <atomic>
#include <chrono>
#include <list>
#include <thread>

namespace harpoon {
namespace execution {

class processing_unit : public hardware_component {
public:
	using hardware_component::hardware_component;

	virtual void prepare() override;

	virtual void boot() override;
	virtual void shutdown() override;

	void add_breakpoint(const breakpoint &breakpoint) {
		_breakpoints.push_back(breakpoint);
	}

	const execution_unit_ptr &get_execution_unit() const {
		return _execution_unit;
	}

	std::uint_fast64_t get_executed_instructions() const {
		return _executed_instructions;
	}

	void enable_disassemble() {
		set_disassemble(true);
	}

	void disable_disassemble() {
		set_disassemble(false);
	}

	void set_disassemble(bool disassemble) {
		_disassemble = disassemble;
	}

	void set_stats_interval(std::uint64_t interval) {
		_stats_interval = interval;
	}

	void set_current_instruction(const instruction &instruction) {
		_current_instruction = instruction;
		if (_disassemble) {
			disassemble_instruction();
		}
		if (_stats_interval > 0 && (_executed_instructions % _stats_interval) == 0) {
			log_stats();
			new_stats_checkpoint();
		}
		process_breakpoints();
		_executed_instructions++;
	}

	const instruction &get_current_instruction() const {
		return _current_instruction;
	}

	std::uint32_t execute_instruction();

	virtual void disassemble_instruction();

	virtual void log_state(log::message::Level level = log::message::Level::DEBUG) const override;
	virtual void log_registers(log::message::Level level) const;

	virtual void new_stats_checkpoint();
	virtual void log_stats(log::message::Level level = log::message::Level::DEBUG);

	virtual ~processing_unit() override;

private:
	void process_breakpoints() {
		for (const auto &breakpoint : _breakpoints) {
			if (breakpoint.check_condition(this)) {
				log(component_debug << "EXECUTION BREAKPOINT");
				disassemble_instruction();
				breakpoint.do_action(this);
			}
		}
	}

	execution_unit_ptr _execution_unit{};
	std::uint_fast64_t _executed_instructions{};
	std::uint64_t _stats_interval{};
	bool _disassemble{};
	std::list<breakpoint> _breakpoints{};
	instruction _current_instruction{};
	std::chrono::high_resolution_clock::time_point _stats_checkpoint_start{}, _run_start{};
	std::uint64_t _stats_checkpoint_executed_instruction{};
};

using processing_unit_ptr = std::shared_ptr<processing_unit>;

} // namespace execution
} // namespace harpoon

#endif
