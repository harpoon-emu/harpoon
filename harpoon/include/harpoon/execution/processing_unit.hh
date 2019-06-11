#ifndef HARPOON_EXECUTION_PROCESSING_UNIT_HH
#define HARPOON_EXECUTION_PROCESSING_UNIT_HH

#include "harpoon/harpoon.hh"

#include "harpoon/execution/breakpoint.hh"
#include "harpoon/execution/cycle.hh"
#include "harpoon/execution/execution_unit.hh"
#include "harpoon/execution/instruction.hh"
#include "harpoon/hardware_component.hh"

#include <atomic>
#include <list>
#include <thread>

namespace harpoon {
namespace execution {

class processing_unit : public hardware_component {
public:
	using hardware_component::hardware_component;

	virtual void prepare();

	virtual void boot();
	virtual void shutdown();

	virtual void run();

	cycle wait_for_cycle(std::uint_fast64_t cycles = 1);

	cycle wait_for_next_cycle() {
		return wait_for_cycle(1);
	}

	virtual std::uint_fast64_t begin_execution() = 0;
	virtual std::uint_fast64_t fetch_decode(instruction_handler &instruction_handler,
	                                        disassemble_handler &disassemble_handler)
	    = 0;
	virtual std::uint_fast64_t execute(instruction_handler &instruction_handler);

	void add_breakpoint(const breakpoint &breakpoint) {
		_breakpoints.push_back(breakpoint);
	}

	bool is_running() const {
		return _running;
	}

	execution_unit_ptr get_execution_unit() const {
		return _execution_unit.lock();
	}

	cycle get_cycle() const {
		return _cycle;
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

	virtual void log_state(log::message::Level level = log::message::Level::DEBUG) const;
	virtual void log_registers(log::message::Level level) const;

	virtual ~processing_unit();

private:
	execution_unit_weak_ptr _execution_unit{};
	std::atomic_bool _running{false};
	std::unique_ptr<std::thread> _thread{};
	clock::tick _last_tick{};
	atomic_cycle _cycle{};
	std::atomic_uint_fast64_t _executed_instructions{};
	bool _disassemble{};
	std::list<breakpoint> _breakpoints{};
};

using processing_unit_ptr = std::shared_ptr<processing_unit>;
using processing_unit_weak_ptr = std::weak_ptr<processing_unit>;

} // namespace execution
} // namespace harpoon

#endif
