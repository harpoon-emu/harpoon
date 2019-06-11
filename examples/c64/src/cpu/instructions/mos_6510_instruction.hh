#ifndef CPU_INSTRUCTIONS_MOS_6510_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_MOS_6510_INSTRUCTION_HH

#include "../mos_6510.hh"

#include "harpoon/execution/instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, std::size_t LEN, std::uint_fast64_t CYCLES>
class mos_6510_instruction : public harpoon::execution::instruction<mos_6510> {
public:
	static constexpr const std::uint8_t OPCODE = OP;
	static constexpr const std::uint_fast64_t CYCLES_EXECUTE = CYCLES;
	static constexpr const std::size_t LENGTH = LEN;

	template<typename T>
	void disassemble_hex(std::ostream &stream, T value) const {
		stream << std::uppercase << std::hex << std::setw(sizeof(T) << 1) << std::setfill('0')
		       << static_cast<std::uint64_t>(value);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream);
	}

protected:
	template<typename T>
	void push(T val) {
		this->get_cpu()->get_memory()->set(
		    mos_6510::STACK_ADDRESS + this->get_cpu()->get_registers().SP - sizeof(T) + 1, val);
		this->get_cpu()->get_registers().SP -= sizeof(T);
	}

	template<typename T>
	void pop(T &val) {
		this->get_cpu()->get_memory()->get(
		    mos_6510::STACK_ADDRESS + this->get_cpu()->get_registers().SP + 1, val);
		this->get_cpu()->get_registers().SP += sizeof(T);
	}

	void mos_disassemble(std::ostream &stream) const {
		disassemble_hex(stream,
		                static_cast<std::uint16_t>(this->get_cpu()->get_registers().PC - LEN));
		stream << ": ";
		disassemble_hex(stream, OPCODE);
		stream << " ";
	}
};

template<std::uint8_t OP, std::uint_fast64_t CYCLES>
class mos_6510_nullary_instruction : public mos_6510_instruction<OP, 1, CYCLES> {
public:
	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "");
	}

protected:
	void mos_disassemble(std::ostream &stream, const std::string &mnemonic) const {
		mos_6510_instruction<OP, 1, CYCLES>::mos_disassemble(stream);
		stream << "         " << mnemonic;
	}
};

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class mos_6510_unary_instruction : public mos_6510_instruction<OP, 1 + sizeof(OPERAND), CYCLES> {
public:
	void decode() {
		this->get_cpu()->get_decoder()->get_program_code(_operand, 1);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble(stream, "");
	}

protected:
	template<typename T>
	void get_zero_page(T &val) {
		this->get_cpu()->get_memory()->get(_operand & 0xff, val);
	}

	template<typename T>
	void get_zero_page_x(T &val) {
		this->get_cpu()->get_memory()->get((_operand & 0xff) + this->get_cpu()->get_registers().X,
		                                   val);
	}

	template<typename T>
	void get_zero_page_y(T &val) {
		this->get_cpu()->get_memory()->get((_operand & 0xff) + this->get_cpu()->get_registers().Y,
		                                   val);
	}

	template<typename T>
	void get_absolute(T &val) {
		this->get_cpu()->get_memory()->get(_operand, val);
	}

	template<typename T>
	void get_absolute_x(T &val) {
		this->get_cpu()->get_memory()->get(_operand + this->get_cpu()->get_registers().X, val);
	}

	template<typename T>
	void get_absolute_y(T &val) {
		this->get_cpu()->get_memory()->get(_operand + this->get_cpu()->get_registers().Y, val);
	}

	template<typename T>
	void get_indirect_x(T &val) {
		std::uint16_t pointer{};
		this->get_cpu()->get_memory()->get((_operand & 0xff) + this->get_cpu()->get_registers().X,
		                                   pointer);
		this->get_cpu()->get_memory()->get(pointer, val);
	}

	template<typename T>
	void get_indirect_y(T &val) {
		std::uint16_t pointer{};
		this->get_cpu()->get_memory()->get(_operand & 0xff, pointer);
		this->get_cpu()->get_memory()->get(pointer + this->get_cpu()->get_registers().Y, val);
	}

	template<typename T>
	void set_zero_page(T val) {
		this->get_cpu()->get_memory()->set(_operand & 0xff, val);
	}

	template<typename T>
	void set_zero_page_x(T val) {
		this->get_cpu()->get_memory()->set((_operand & 0xff) + this->get_cpu()->get_registers().X,
		                                   val);
	}

	template<typename T>
	void set_zero_page_y(T val) {
		this->get_cpu()->get_memory()->set((_operand & 0xff) + this->get_cpu()->get_registers().Y,
		                                   val);
	}

	template<typename T>
	void set_absolute(T val) {
		this->get_cpu()->get_memory()->set(_operand, val);
	}

	template<typename T>
	void set_absolute_x(T val) {
		this->get_cpu()->get_memory()->set(_operand + this->get_cpu()->get_registers().X, val);
	}

	template<typename T>
	void set_absolute_y(T val) {
		this->get_cpu()->get_memory()->set(_operand + this->get_cpu()->get_registers().Y, val);
	}

	template<typename T>
	void set_indirect_x(T val) {
		std::uint16_t pointer{};
		this->get_cpu()->get_memory()->get((_operand & 0xff) + this->get_cpu()->get_registers().X,
		                                   pointer);
		this->get_cpu()->get_memory()->set(pointer, val);
	}

	template<typename T>
	void set_indirect_y(T val) {
		std::uint16_t pointer{};
		this->get_cpu()->get_memory()->get(_operand & 0xff, pointer);
		this->get_cpu()->get_memory()->set(pointer + this->get_cpu()->get_registers().Y, val);
	}

	void disassemble_operand(std::ostream &stream, std::uint8_t operand) const {
		this->disassemble_hex(stream, operand);
		stream << "   ";
	}

	void disassemble_operand(std::ostream &stream, std::uint16_t operand) const {
		this->disassemble_hex(stream, static_cast<std::uint8_t>(operand & 0xff));
		stream << " ";
		this->disassemble_hex(stream, static_cast<std::uint8_t>((operand >> 8) & 0xff));
	}

	void mos_disassemble(std::ostream &stream, const std::string &mnemonic) const {
		mos_6510_instruction<OP, 1 + sizeof(OPERAND), CYCLES>::mos_disassemble(stream);
		disassemble_operand(stream, _operand);
		stream << "    " << mnemonic << " ";
	}

	void mos_disassemble_immediate(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "#$";
		this->disassemble_hex(stream, _operand);
	}

	void mos_disassemble_absolute(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "$";
		this->disassemble_hex(stream, _operand);
	}

	void mos_disassemble_absolute_x(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "$";
		this->disassemble_hex(stream, _operand);
		stream << ",X";
	}

	void mos_disassemble_absolute_y(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "$";
		this->disassemble_hex(stream, _operand);
		stream << ",Y";
	}

	void mos_disassemble_indirect(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "($";
		this->disassemble_hex(stream, _operand);
		stream << ")";
	}

	void mos_disassemble_indirect_x(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "($";
		this->disassemble_hex(stream, _operand);
		stream << ",X)";
	}

	void mos_disassemble_indirect_y(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "($";
		this->disassemble_hex(stream, _operand);
		stream << "),Y";
	}

	void mos_disassemble_relative(std::ostream &stream, const std::string &mnemonic) const {
		mos_disassemble(stream, mnemonic);
		stream << "$";
		this->disassemble_hex(stream,
		                      static_cast<std::uint16_t>(this->get_cpu()->get_registers().PC
		                                                 + static_cast<std::int8_t>(_operand)));
		stream << " [#$";
		this->disassemble_hex(stream, _operand);
		stream << "]";
	}

	OPERAND _operand{};
};

class mos_6510_arith_instruction {
protected:
	void update_flag_Z(mos_6510 *cpu, std::uint8_t val) {
		cpu->get_registers().P.Z() = (val == 0);
	}

	void update_flag_N(mos_6510 *cpu, std::uint8_t val) {
		cpu->get_registers().P.N() = ((val & 0x80) == 0x80);
	}

	void update_flags_NZ(mos_6510 *cpu, std::uint8_t val) {
		update_flag_Z(cpu, val);
		update_flag_N(cpu, val);
	}
};

class mos_6510_a_instruction : public mos_6510_arith_instruction {
protected:
	using mos_6510_arith_instruction::update_flags_NZ;
	void update_flags_NZ(mos_6510 *cpu) {
		update_flags_NZ(cpu, cpu->get_registers().A);
	}
};

class mos_6510_x_instruction : public mos_6510_arith_instruction {
protected:
	using mos_6510_arith_instruction::update_flags_NZ;
	void update_flags_NZ(mos_6510 *cpu) {
		update_flags_NZ(cpu, cpu->get_registers().X);
	}
};

class mos_6510_y_instruction : public mos_6510_arith_instruction {
protected:
	using mos_6510_arith_instruction::update_flags_NZ;
	void update_flags_NZ(mos_6510 *cpu) {
		update_flags_NZ(cpu, cpu->get_registers().Y);
	}
};

template<std::uint8_t OP, std::uint_fast64_t CYCLES>
class mos_6510_a_nullary_instruction : public mos_6510_nullary_instruction<OP, CYCLES>,
                                       public mos_6510_a_instruction {};

template<std::uint8_t OP, std::uint_fast64_t CYCLES>
class mos_6510_x_nullary_instruction : public mos_6510_nullary_instruction<OP, CYCLES>,
                                       public mos_6510_x_instruction {};

template<std::uint8_t OP, std::uint_fast64_t CYCLES>
class mos_6510_y_nullary_instruction : public mos_6510_nullary_instruction<OP, CYCLES>,
                                       public mos_6510_y_instruction {};

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class mos_6510_a_unary_instruction : public mos_6510_unary_instruction<OP, OPERAND, CYCLES>,
                                     public mos_6510_a_instruction {};

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class mos_6510_x_unary_instruction : public mos_6510_unary_instruction<OP, OPERAND, CYCLES>,
                                     public mos_6510_x_instruction {};

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class mos_6510_y_unary_instruction : public mos_6510_unary_instruction<OP, OPERAND, CYCLES>,
                                     public mos_6510_y_instruction {};

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class mos_6510_mem_unary_instruction : public mos_6510_unary_instruction<OP, OPERAND, CYCLES>,
                                       public mos_6510_arith_instruction {};

template<std::uint8_t OP, std::uint_fast64_t CYCLES>
class mos_6510_relative_branch_instruction
    : public mos_6510_unary_instruction<OP, std::uint8_t, CYCLES> {
protected:
	void branch(bool condition) {
		if (condition) {
			std::int8_t offset = static_cast<std::int8_t>(this->_operand);
			this->get_cpu()->get_registers().PC += offset;
		}
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
