#ifndef CPU_MOS_6510_HH
#define CPU_MOS_6510_HH

#include "../memory/memory.hh"
#include "mos_6510_flags.hh"

#include "harpoon/execution/basic_register.hh"
#include "harpoon/execution/processing_unit.hh"
#include "harpoon/memory/io_memory.hh"
#include "harpoon/memory/linear_random_access_memory.hh"
#include "harpoon/memory/memory.hh"

#include <array>

namespace c64 {
namespace hw {
namespace cpu {

class mos_6510 : public harpoon::execution::processing_unit {
public:
	static constexpr const std::uint16_t STACK_ADDRESS = 0x100;
	static constexpr const std::uint16_t RESET_VECTOR = 0xfffc;

	struct registers {
		harpoon::execution::basic_register<std::uint8_t> A{};
		harpoon::execution::basic_register<std::uint8_t> X{};
		harpoon::execution::basic_register<std::uint8_t> Y{};
		harpoon::execution::basic_register<std::uint8_t> SP{};
		harpoon::execution::basic_register<std::uint16_t> PC{};
		harpoon::execution::basic_register<std::uint8_t> IR{};
		mos_6510_flags P{};
	};

	using harpoon::execution::processing_unit::processing_unit;

	using zero_page_memory
	    = harpoon::memory::io_memory<harpoon::memory::linear_random_access_memory>;
	using zero_page_memory_weak_ptr = std::weak_ptr<zero_page_memory>;

	using instruction_factory = std::function<harpoon::execution::instruction(mos_6510 *)>;

	union internal_memory_access {
		struct {
			union {
				std::uint8_t previous;
				std::uint8_t l;
			};
			union {
				std::uint8_t current;
				std::uint8_t h;
			};
		} b;
		std::uint8_t _b[2];
		std::uint16_t w;
	};

	void create();

	virtual void boot() override;

	virtual void step(hardware_component *trigger) override;

	const zero_page_memory_weak_ptr &get_zero_page() const {
		return _zero_page;
	}

	void set_memory(const memory::memory_weak_ptr &memory) {
		_memory = memory;
	}

	memory::memory_ptr get_memory() const {
		return _memory.lock();
	}

	void set_init_PC(std::uint16_t v) {
		_init_PC = v;
	}

	const struct registers &get_registers() const {
		return _registers;
	}

	struct registers &get_registers() {
		return _registers;
	}

	void set_latch(std::uint8_t value) {
		_latch = value;
	}

	void set_A(std::uint8_t value) {
		_registers.A.set(value);
	}

	void set_X(std::uint8_t value) {
		_registers.X.set(value);
	}

	void set_Y(std::uint8_t value) {
		_registers.Y.set(value);
	}

	void set_SP(std::uint8_t value) {
		_registers.SP.set(value);
	}

	void set_PC(std::uint16_t value) {
		_registers.PC.set(value);
	}

	void set_PCL(std::uint8_t value) {
		_registers.PC.set((_registers.PC.get() & 0xFF00) | value);
	}

	void set_PCH(std::uint8_t value) {
		_registers.PC.set(static_cast<std::uint16_t>((static_cast<std::uint16_t>(value) << 8))
		                  | static_cast<std::uint16_t>(_registers.PC.get() & 0xFF));
	}

	void set_IR(std::uint8_t value) {
		_registers.IR.set(value);
	}

	void set_P(std::uint8_t value) {
		_registers.P.set_flags(value);
	}

	void set_flag_N(bool b) {
		_registers.P.N() = b;
	}

	void set_flag_Z(bool b) {
		_registers.P.Z() = b;
	}

	void set_flag_C(bool b) {
		_registers.P.C() = b;
	}

	void set_flag_I(bool b) {
		_registers.P.I() = b;
	}

	void set_flag_D(bool b) {
		_registers.P.D() = b;
	}

	void set_flag_V(bool b) {
		_registers.P.V() = b;
	}

	std::uint8_t get_latch() const {
		return _latch;
	}

	std::uint8_t get_A() const {
		return _registers.A;
	}

	std::uint8_t get_X() const {
		return _registers.X;
	}

	std::uint8_t get_Y() const {
		return _registers.Y;
	}

	std::uint8_t get_SP() const {
		return _registers.SP;
	}

	std::uint16_t get_PC() const {
		return _registers.PC;
	}

	std::uint8_t get_PCL() const {
		return _registers.PC & 0xFF;
	}

	std::uint8_t get_PCH() const {
		return _registers.PC >> 8;
	}

	std::uint8_t get_IR() const {
		return _registers.IR;
	}

	std::uint8_t get_P() const {
		return _registers.P.get_flags();
	}

	bool get_flag_N() const {
		return _registers.P.N();
	}

	bool get_flag_Z() const {
		return _registers.P.Z();
	}

	bool get_flag_C() const {
		return _registers.P.C();
	}

	bool get_flag_I() const {
		return _registers.P.I();
	}

	bool get_flag_D() const {
		return _registers.P.D();
	}

	bool get_flag_V() const {
		return _registers.P.V();
	}

	void fetch_opcode();
	void get_program_code(uint8_t &data);

	void internal_read(harpoon::memory::address address);
	void internal_read_program_code();

	const union internal_memory_access &get_internal_memory_access() const {
		return _internal_memory_access;
	}

	void fetch_indirect_pointer(bool x_index);

	std::uint16_t get_indirect_pointer() const {
		return _indirect_pointer;
	}

	void stack_push(std::uint8_t v);
	void stack_pull(std::uint8_t &v);

	void log_registers(harpoon::log::message::Level level) const override;

	virtual ~mos_6510() override;

private:
	void create_zero_page();

	void init_registers();
	void init_zero_page();

	void init_instructions();

	template<typename T>
	void register_instruction_factory();

	void boot_sequence();

	void decode_instruction();

	void _zp_01_processor_port_out(const harpoon::memory::address &address, std::uint8_t value);

	struct registers _registers {};
	memory::memory_weak_ptr _memory{};
	zero_page_memory_weak_ptr _zero_page{};

	std::array<instruction_factory, 256> _instruction_factories{};

	bool _boot_sequence{};
	bool _opcode_ready{};
	std::uint8_t _latch{};
	union internal_memory_access _internal_memory_access {};
	std::uint16_t _indirect_pointer{};

	std::uint16_t _init_PC{0xFFFF};

	std::uint8_t _prev_IR{};
};

} // namespace cpu
} // namespace hw
} // namespace c64

#endif
