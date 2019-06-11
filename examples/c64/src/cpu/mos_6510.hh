#ifndef CPU_MOS_6510_HH
#define CPU_MOS_6510_HH

#include "../memory/memory.hh"
#include "mos_6510_flags.hh"

#include "harpoon/execution/basic_register.hh"
#include "harpoon/execution/processing_unit.hh"
#include "harpoon/memory/io_memory.hh"
#include "harpoon/memory/linear_random_access_memory.hh"
#include "harpoon/memory/memory.hh"

namespace commodore {
namespace cpu {

class mos_6510_decoder;

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

	void create();

	virtual void boot();

	virtual std::uint_fast64_t begin_execution();
	virtual std::uint_fast64_t
	fetch_decode(harpoon::execution::instruction_handler &instruction_handler,
	             harpoon::execution::disassemble_handler &disassemble_handler);

	const zero_page_memory_weak_ptr &get_zero_page() const {
		return _zero_page;
	}

	void set_memory(const memory::memory_weak_ptr &memory) {
		_memory = memory;
	}

	memory::memory_ptr get_memory() const {
		return _memory.lock();
	}

	std::shared_ptr<mos_6510_decoder> get_decoder() const {
		return _decoder.lock();
	}

	const struct registers &get_registers() const {
		return _registers;
	}

	struct registers &get_registers() {
		return _registers;
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

	void set_IR(std::uint8_t value) {
		_registers.IR.set(value);
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

	std::uint8_t get_IR() const {
		return _registers.IR;
	}

	void log_registers(harpoon::log::message::Level level) const;

	virtual ~mos_6510();

private:
	void create_zero_page();

	void init_registers();
	void init_zero_page();

	void _zp_01_processor_port_out(const harpoon::memory::address &address, std::uint8_t value);

	struct registers _registers {};
	memory::memory_weak_ptr _memory{};
	zero_page_memory_weak_ptr _zero_page{};
	std::weak_ptr<mos_6510_decoder> _decoder{};
};

} // namespace cpu
} // namespace commodore

#endif
