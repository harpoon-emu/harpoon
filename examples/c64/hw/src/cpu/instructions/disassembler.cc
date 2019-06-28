#include "disassembler.hh"

#include "../mos_6510.hh"

#include <iomanip>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace disassembler {

base::~base() {}

void base::operator()(const harpoon::execution::instruction &instruction, std::ostream &stream) {
	mos_6510 *cpu = static_cast<mos_6510 *>(instruction.get_processing_unit());

	std::uint16_t pc = cpu->get_PC() - 1;
	for (std::uint16_t i = 0; i < _length; i++) {
		std::uint8_t v;
		cpu->get_memory()->get(pc + i, v);
		_bytes[i] = v;
	}

	stream << std::setfill('0') << std::setw(4) << std::hex << std::uppercase;
	stream << pc << ": ";

	for (std::uint16_t i = 0; i < 3; i++) {
		if (i >= _length) {
			stream << "  ";
		} else {
			out_byte_raw(stream, _bytes[i]);
		}
		stream << " ";
	}
	stream << " | ";

	stream << _mnemonic;
	if (_length > 1) {
		stream << std::string("\t");
	}
	disassemble(instruction, stream);
}

void base::out_byte_raw(std::ostream &stream, std::uint8_t v) {
	stream << std::setfill('0') << std::setw(2) << std::hex << std::uppercase;
	stream << static_cast<std::uint32_t>(v);
}

void base::out_byte_hex(std::ostream &stream, std::uint8_t v) {
	stream << "$";
	out_byte_raw(stream, v);
}

void base::out_word_raw(std::ostream &stream, std::uint8_t lo, std::uint8_t hi) {
	out_byte_raw(stream, hi);
	out_byte_raw(stream, lo);
}

void base::out_word_hex(std::ostream &stream, std::uint8_t lo, std::uint8_t hi) {
	stream << "$";
	out_word_raw(stream, lo, hi);
}

void implied::disassemble(const harpoon::execution::instruction &, std::ostream &) {}

void accumulator::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	stream << " A";
}

void immediate::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	stream << "#";
	out_operand_byte(stream);
}

void zero_page::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_byte(stream);
}

void zero_page_x::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_byte(stream);
	stream << ",X";
}

void zero_page_y::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_byte(stream);
	stream << ",Y";
}

void absolute::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_word(stream);
}

void absolute_x::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_word(stream);
	stream << ",X";
}

void absolute_y::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_word(stream);
	stream << ",Y";
}

void indirect::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	stream << "(";
	out_operand_word(stream);
	stream << ")";
}

void indirect_x::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	stream << "(";
	out_operand_byte(stream);
	stream << ",X";
	stream << ")";
}

void indirect_y::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	stream << "(";
	out_operand_byte(stream);
	stream << ")";
	stream << ",Y";
}

void relative::disassemble(const harpoon::execution::instruction &, std::ostream &stream) {
	out_operand_byte(stream);
}

} // namespace disassembler
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
