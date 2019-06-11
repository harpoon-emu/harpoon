#ifndef CPU_INSTRUCTIONS_CMP_HH
#define CPU_INSTRUCTIONS_CMP_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class cmp : public mos_6510_mem_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_cmp(std::uint8_t val) {
		std::uint8_t x = this->get_cpu()->get_registers().A;
		std::uint8_t y = val;
		std::uint8_t res = x - y;
		this->get_cpu()->get_registers().P.N() = ((res & 0x80) == 0x80);
		this->get_cpu()->get_registers().P.Z() = (res == 0x00);
		this->get_cpu()->get_registers().P.C() = (x >= y);
	}
};

class cmp_immediate : public cmp<0xC9, std::uint8_t, 2> {
public:
	void execute() {
		do_cmp(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "CMP");
	}
};

class cmp_zero_page : public cmp<0xC5, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t mem{};
		get_zero_page(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "CMP");
	}
};

class cmp_zero_page_x : public cmp<0xD5, std::uint8_t, 4> {
public:
	void execute() {
		std::uint8_t mem{};
		get_zero_page_x(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "CMP");
	}
};

class cmp_absolute : public cmp<0xCD, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t mem{};
		get_absolute(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "CMP");
	}
};

class cmp_absolute_x : public cmp<0xDD, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t mem{};
		get_absolute_x(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "CMP");
	}
};

class cmp_absolute_y : public cmp<0xD9, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t mem{};
		get_absolute_y(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "CMP");
	}
};

class cmp_indirect_x : public cmp<0xC1, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t mem{};
		get_indirect_x(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "CMP");
	}
};

class cmp_indirect_y : public cmp<0xD1, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t mem{};
		get_indirect_y(mem);
		do_cmp(mem);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "CMP");
	}
};

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
