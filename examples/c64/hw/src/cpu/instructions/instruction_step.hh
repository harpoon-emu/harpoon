#ifndef CPU_INSTRUCTIONS_INSTRUCTION_STEP_HH
#define CPU_INSTRUCTIONS_INSTRUCTION_STEP_HH

#include "../mos_6510.hh"

#include "harpoon/execution/instruction.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

class instruction_step {
public:
	instruction_step(const harpoon::execution::instruction &instruction)
	    : _instruction{instruction} {
		_cpu = static_cast<mos_6510 *>(instruction.get_processing_unit());
	}

	virtual std::uint32_t check() = 0;
	virtual std::uint32_t step() {
		execute();
		return _delay;
	}
	virtual void execute() = 0;

	template<typename T, T (mos_6510::*get_reg)() const>
	void fetch_register(T &v, bool update_nz = true) {
		v = (get_cpu()->*get_reg)();
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	void fetch_immediate(std::uint8_t &v, bool update_nz = true) {
		get_cpu()->get_program_code(v);
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	void fetch_zero_page(std::uint8_t &v, bool update_nz = true) {
		fetch_zero_page_index(v, 0, update_nz);
	}

	template<std::uint8_t (mos_6510::*get_reg)() const>
	void fetch_zero_page_reg(std::uint8_t &v, bool update_nz = true) {
		fetch_zero_page_index(v, (get_cpu()->*get_reg)(), update_nz);
	}

	void fetch_absolute(std::uint8_t &v, bool update_nz = true) {
		fetch_absolute_index(v, 0, update_nz);
	}

	template<std::uint8_t (mos_6510::*get_reg)() const>
	void fetch_absolute_reg(std::uint8_t &v, bool update_nz = true) {
		fetch_absolute_index(v, (get_cpu()->*get_reg)(), update_nz);
	}

	void fetch_indirect(std::uint8_t &v, bool update_nz = true) {
		fetch_indirect_index(v, 0, update_nz);
	}

	void fetch_indirect_y(std::uint8_t &v, bool update_nz = true) {
		fetch_indirect_index(v, get_cpu()->get_Y(), update_nz);
	}

	void store_zero_page(std::uint8_t v) {
		store_zero_page_index(0, v);
	}

	template<std::uint8_t (mos_6510::*get_reg)() const>
	void store_zero_page_reg(std::uint8_t v) {
		store_zero_page_index((get_cpu()->*get_reg)(), v);
	}

	void store_absolute(std::uint8_t v) {
		store_absolute_index(0, v);
	}

	template<std::uint8_t (mos_6510::*get_reg)() const>
	void store_absolute_reg(std::uint8_t v) {
		store_absolute_index((get_cpu()->*get_reg)(), v);
	}

	void store_indirect(std::uint8_t v) {
		store_indirect_index(0, v);
	}

	void store_indirect_y(std::uint8_t v) {
		store_indirect_index(get_cpu()->get_Y(), v);
	}

	virtual ~instruction_step();

protected:
	mos_6510 *get_cpu() const {
		return _cpu;
	}

	void set_delay(std::uint32_t d) {
		_delay = d;
	}

	void fetch_memory(std::uint8_t &v, std::uint16_t address, std::uint8_t index, bool update_nz) {
		std::uint16_t a = address + index;
		get_cpu()->get_memory()->get(a, v);
		if (update_nz) {
			update_flags_NZ(v);
		}

		if ((a & 0xFF00) != (address & 0xFF00)) {
			set_delay(2);
		}
	}

	void fetch_zero_page_index(std::uint8_t &v, std::uint8_t index, bool update_nz) {
		fetch_memory(v, (get_cpu()->get_internal_memory_access().b.current + index) & 0xFF, 0,
		             update_nz);
	}

	void fetch_absolute_index(std::uint8_t &v, std::uint8_t index, bool update_nz) {
		fetch_memory(v, get_cpu()->get_internal_memory_access().w, index, update_nz);
	}

	void fetch_indirect_index(std::uint8_t &v, std::uint8_t index, bool update_nz) {
		fetch_memory(v, get_cpu()->get_indirect_pointer(), index, update_nz);
	}

	void store_memory(std::uint16_t address, std::uint8_t index, std::uint8_t v) {
		std::uint16_t a = address + index;
		get_cpu()->get_memory()->set(a, v);
	}

	void store_zero_page_index(std::uint8_t index, std::uint8_t v) {
		store_memory((get_cpu()->get_internal_memory_access().b.current + index) & 0xFF, 0, v);
	}

	void store_absolute_index(std::uint8_t index, std::uint8_t v) {
		store_memory(get_cpu()->get_internal_memory_access().w, index, v);
	}

	void store_indirect_index(std::uint8_t index, std::uint8_t v) {
		store_memory(get_cpu()->get_indirect_pointer(), index, v);
	}

	template<typename T>
	void update_flag_Z(T v) {
		get_cpu()->get_registers().P.Z() = (v == 0);
	}

	template<typename T>
	void update_flag_N(T v) {
		T h = 1 << ((sizeof(T) * 8) - 1);
		get_cpu()->get_registers().P.N() = ((v & h) == h);
	}

	template<typename T>
	void update_flags_NZ(T v) {
		update_flag_Z(v);
		update_flag_N(v);
	}

private:
	const harpoon::execution::instruction _instruction{};
	mos_6510 *_cpu{};
	std::uint32_t _delay{1};
};

class instruction_step_read : public instruction_step {
public:
	using instruction_step::instruction_step;

	virtual std::uint32_t check() override;
};

class instruction_step_fetch_next : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual std::uint32_t step() override;
};

class instruction_step_write : public instruction_step {
public:
	using instruction_step::instruction_step;

	virtual std::uint32_t check() override;
};

class internal_read : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

class internal_write : public instruction_step_write {
public:
	using instruction_step_write::instruction_step_write;

	virtual void execute() override;
};

class fetch_program_code : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override;
};

template<bool x_index>
class fetch_indirect_pointer : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		get_cpu()->fetch_indirect_pointer(x_index);
	}
};

template<void (mos_6510::*set_reg)(std::uint8_t), bool update_nz>
class stack_pull : public instruction_step_read {
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		std::uint8_t v;
		get_cpu()->stack_pull(v);
		(get_cpu()->*set_reg)(v);
		if (update_nz) {
			update_flags_NZ(v);
		}
	}
};

template<std::uint8_t (mos_6510::*get_reg)() const>
class stack_push : public instruction_step_write {
	using instruction_step_write::instruction_step_write;

	virtual void execute() override {
		std::uint8_t v = (get_cpu()->*get_reg)();
		get_cpu()->stack_push(v);
	}
};

template<void (mos_6510::*set_f)(bool), bool value>
class set_flag : public instruction_step_read {
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		(get_cpu()->*set_f)(value);
	}
};

template<typename T>
std::uint32_t check_fn(const harpoon::execution::instruction &instruction) {
	T step(instruction);
	return step.check();
}

template<typename T>
std::uint32_t step_fn(const harpoon::execution::instruction &instruction) {
	T step(instruction);
	return step.step();
}

template<typename T>
harpoon::execution::instruction::step_handlers make_instruction_step() {
	return {check_fn<T>, step_fn<T>};
}

template<void (mos_6510::*set_f)(bool), bool value>
harpoon::execution::instruction set_flag_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(cpu, {make_instruction_step<set_flag<set_f, value>>()});
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
