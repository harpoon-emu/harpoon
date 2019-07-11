#ifndef CPU_INSTRUCTIONS_ARITH_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_ARITH_INSTRUCTION_HH

#include "../mos_6510.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

class arith : public instruction_step_read {
public:
	using instruction_step_read::instruction_step_read;

	virtual ~arith();

	template<typename T>
	void inc(T &v, bool update_nz = true) {
		v++;
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	template<typename T>
	void dec(T &v, bool update_nz = true) {
		v--;
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	void and_(std::uint8_t &v, std::uint8_t operand, bool update_nz = true) {
		v &= operand;
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	void or_(std::uint8_t &v, std::uint8_t operand, bool update_nz = true) {
		v |= operand;
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	void eor(std::uint8_t &v, std::uint8_t operand, bool update_nz = true) {
		v ^= operand;
		if (update_nz) {
			update_flags_NZ(v);
		}
	}

	void asl(std::uint8_t &v, bool update_nzc = true) {
		std::uint8_t x = v;
		v <<= 1;
		if (update_nzc) {
			update_flags_NZ(v);
			get_cpu()->set_flag_C((x & 0x80) == 0x80);
		}
	}

	void lsr(std::uint8_t &v, bool update_nzc = true) {
		std::uint8_t x = v;
		v >>= 1;
		if (update_nzc) {
			update_flags_NZ(v);
			get_cpu()->set_flag_C((x & 0x01) == 0x01);
		}
	}

	void rol(std::uint8_t &v, bool update_nzc = true) {
		std::uint8_t x = v;
		v <<= 1;
		v |= get_cpu()->get_flag_C() ? 0x01 : 0x00;
		if (update_nzc) {
			update_flags_NZ(v);
			get_cpu()->set_flag_C((x & 0x80) == 0x80);
		}
	}

	void ror(std::uint8_t &v, bool update_nzc = true) {
		std::uint8_t x = v;
		v >>= 1;
		v |= get_cpu()->get_flag_C() ? 0x80 : 0x00;
		if (update_nzc) {
			update_flags_NZ(v);
			get_cpu()->set_flag_C((x & 0x01) == 0x01);
		}
	}

	void bit(std::uint8_t &a, std::uint8_t m, bool) {
		update_flags_NZ(static_cast<std::uint8_t>(a & m));
		get_cpu()->set_flag_V((m & 0x40) == 0x40);
		get_cpu()->set_flag_N((m & 0x80) == 0x80);
	}

	void adc(std::uint8_t &v, std::uint8_t operand, bool update_nzcv = true) {
		std::uint8_t x = v, y = operand;
		std::uint16_t res = {};
		res = x + y;
		if (get_cpu()->get_flag_C()) {
			res++;
		}
		v = static_cast<std::uint8_t>(res & 0xff);
		if (update_nzcv) {
			update_flags_NZ(v);
			get_cpu()->set_flag_V(((~(x ^ y)) & (x ^ res) & 0x80) == 0x80);
			get_cpu()->set_flag_C(res > 0xff);
		}
	}

	void sbc(std::uint8_t &v, std::uint8_t operand, bool update_nzcv = true) {
		std::uint8_t x = v, y = ~operand;
		std::uint16_t res = {};
		res = x + y;
		if (get_cpu()->get_flag_C()) {
			res--;
		}
		v = static_cast<std::uint8_t>(res & 0xff);
		if (update_nzcv) {
			update_flags_NZ(v);
			get_cpu()->set_flag_V(((~(x ^ y)) & (x ^ res) & 0x80) == 0x80);
			get_cpu()->set_flag_C(res > 0xff);
		}
	}
};

template<typename T, T (mos_6510::*get_reg)() const, void (arith::*op)(T &, bool),
         void (mos_6510::*set_reg)(T), bool update_flags>
class implied_arith : public arith {
public:
	using arith::arith;

	virtual void execute() override {
		T v;
		v = (get_cpu()->*get_reg)();
		(this->*op)(v, update_flags);
		(get_cpu()->*set_reg)(v);
	}
};

template<std::uint8_t (mos_6510::*get_reg)() const, void (arith::*op)(std::uint8_t &, bool),
         void (mos_6510::*set_reg)(std::uint8_t), bool update_flags>
using implied_arith8 = implied_arith<std::uint8_t, get_reg, op, set_reg, update_flags>;

template<std::uint16_t (mos_6510::*get_reg)() const, void (arith::*op)(std::uint16_t &, bool),
         void (mos_6510::*set_reg)(std::uint16_t), bool update_flags>
using implied_arith16 = implied_arith<std::uint16_t, get_reg, op, set_reg, update_flags>;

template<std::uint8_t (mos_6510::*get_reg)() const, void (arith::*op)(std::uint8_t &, bool),
         void (mos_6510::*set_reg)(std::uint8_t)>
harpoon::execution::instruction implied_arith_factory(harpoon::execution::processing_unit *cpu,
                                                      const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<implied_arith8<get_reg, op, set_reg, true>>(),
	    },
	    disassembler::implied(mnemonic));
}

template<void (arith::*op)(std::uint8_t &, bool)>
harpoon::execution::instruction accumulator_arith_factory(harpoon::execution::processing_unit *cpu,
                                                          const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<implied_arith8<&mos_6510::get_A, op, &mos_6510::set_A, true>>(),
	    },
	    disassembler::accumulator(mnemonic));
}

template<void (arith::*op)(std::uint8_t &, std::uint8_t, bool),
         void (instruction_step::*fetch)(std::uint8_t &, bool)>
class accumulator_arith : public arith {
public:
	using arith::arith;

	virtual void execute() override {
		std::uint8_t a, m;
		a = get_cpu()->get_A();
		(this->*fetch)(m, false);
		(this->*op)(a, m, true);
		get_cpu()->set_A(a);
	}
};

template<void (arith::*op)(std::uint8_t &, bool), void (instruction_step::*store)(std::uint8_t)>
class rmw_arith : public arith {
public:
	using arith::arith;

	virtual void execute() override {
		std::uint8_t a;
		a = get_cpu()->get_latch();
		(this->*op)(a, true);
		(this->*store)(a);
	}
};

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
