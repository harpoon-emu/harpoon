#ifndef CPU_INSTRUCTIONS_ADC_HH
#define CPU_INSTRUCTIONS_ADC_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

template<std::uint8_t OP, typename OPERAND, std::uint_fast64_t CYCLES>
class adc : public mos_6510_a_unary_instruction<OP, OPERAND, CYCLES> {
protected:
	void do_adc(std::uint8_t val) {
		std::uint8_t x = this->get_cpu()->get_registers().A;
		std::uint8_t y = val;
		std::uint16_t res = {};
		res = x + y;
		if (this->get_cpu()->get_registers().P.C()) {
			res++;
		}
		this->get_cpu()->get_registers().A = (res & 0xff);
		this->update_flags_NZ(this->get_cpu());
		this->get_cpu()->get_registers().P.V() = (((~(x ^ y)) & (x ^ res) & 0x80) == 0x80);
		this->get_cpu()->get_registers().P.C() = (res > 0xff);
	}
};

class adc_immediate : public adc<0x69, std::uint8_t, 2> {
public:
	void execute() {
		do_adc(_operand);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_immediate(stream, "ADC");
	}
};

class adc_zero_page : public adc<0x65, std::uint8_t, 3> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ADC");
	}
};

class adc_zero_page_x : public adc<0x75, std::uint8_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_zero_page_x(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ADC");
	}
};

class adc_absolute : public adc<0x6D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute(stream, "ADC");
	}
};

class adc_absolute_x : public adc<0x7D, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_x(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_x(stream, "ADC");
	}
};

class adc_absolute_y : public adc<0x79, std::uint16_t, 4> {
public:
	void execute() {
		std::uint8_t val{};
		get_absolute_y(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_absolute_y(stream, "ADC");
	}
};

class adc_indirect_x : public adc<0x61, std::uint8_t, 6> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_x(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_x(stream, "ADC");
	}
};

class adc_indirect_y : public adc<0x71, std::uint8_t, 5> {
public:
	void execute() {
		std::uint8_t val{};
		get_indirect_y(val);
		do_adc(val);
	}

	void disassemble(std::ostream &stream) const {
		mos_disassemble_indirect_y(stream, "ADC");
	}
};


} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
