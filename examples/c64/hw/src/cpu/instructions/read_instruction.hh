#ifndef CPU_INSTRUCTIONS_READ_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_READ_INSTRUCTION_HH

#include "../mos_6510.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename T, void (mos_6510::*set_reg)(T), void (instruction_step::*fetch)(T &, bool),
         bool update_nz>
class load_register : public instruction_step_read {
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		T v;
		(this->*fetch)(v, update_nz);
		(get_cpu()->*set_reg)(v);
	}
};

template<void (instruction_step::*fetch)(std::uint8_t &, bool)>
using load_latch = load_register<std::uint8_t, &mos_6510::set_latch, fetch, false>;

template<typename T, T (mos_6510::*get_reg)() const, void (mos_6510::*set_reg)(T), bool update_nz>
using transfer_register
    = load_register<T, set_reg, &instruction_step::fetch_register<T, get_reg>, update_nz>;

template<std::uint8_t (mos_6510::*get_reg)() const,
         void (instruction_step::*fetch)(std::uint8_t &, bool)>
class compare_register : public instruction_step_read {
	using instruction_step_read::instruction_step_read;

	virtual void execute() override {
		std::uint8_t a, m, r;
		a = (get_cpu()->*get_reg)();
		(this->*fetch)(m, false);
		r = a - m;

		get_cpu()->get_registers().P.N() = ((r & 0x80) == 0x80);
		get_cpu()->get_registers().P.Z() = (r == 0x00);
		get_cpu()->get_registers().P.C() = (a >= m);
	}
};

template<typename T, T (mos_6510::*get_reg)() const, void (mos_6510::*set_reg)(T), bool update_nz>
harpoon::execution::instruction transfer_register_factory(harpoon::execution::processing_unit *cpu,
                                                          const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<transfer_register<T, get_reg, set_reg, update_nz>>()},
	    disassembler::implied(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction immediate_read_factory(harpoon::execution::processing_unit *cpu,
                                                       const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<I<&instruction_step::fetch_immediate>>()},
	    disassembler::immediate(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction zero_page_read_factory(harpoon::execution::processing_unit *cpu,
                                                       const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<I<&instruction_step::fetch_zero_page>>(),
	    },
	    disassembler::zero_page(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I,
         std::uint8_t (mos_6510::*get_reg)() const, typename D>
harpoon::execution::instruction
zero_page_index_read_factory(harpoon::execution::processing_unit *cpu,
                             const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<I<&instruction_step::fetch_zero_page_reg<get_reg>>>(),
	    },
	    D(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction zero_page_x_read_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return zero_page_index_read_factory<I, &mos_6510::get_X, disassembler::zero_page_x>(cpu,
	                                                                                    mnemonic);
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction zero_page_y_read_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return zero_page_index_read_factory<I, &mos_6510::get_Y, disassembler::zero_page_y>(cpu,
	                                                                                    mnemonic);
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction absolute_read_factory(harpoon::execution::processing_unit *cpu,
                                                      const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<I<&instruction_step::fetch_absolute>>(),
	    },
	    disassembler::absolute(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I,
         std::uint8_t (mos_6510::*get_reg)() const, typename D>
harpoon::execution::instruction
absolute_index_read_factory(harpoon::execution::processing_unit *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<I<&instruction_step::fetch_absolute_reg<get_reg>>>(),
	    },
	    D(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction absolute_x_read_factory(harpoon::execution::processing_unit *cpu,
                                                        const std::string &mnemonic) {
	return absolute_index_read_factory<I, &mos_6510::get_X, disassembler::absolute_x>(cpu,
	                                                                                  mnemonic);
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction absolute_y_read_factory(harpoon::execution::processing_unit *cpu,
                                                        const std::string &mnemonic) {
	return absolute_index_read_factory<I, &mos_6510::get_Y, disassembler::absolute_y>(cpu,
	                                                                                  mnemonic);
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction indirect_x_read_factory(harpoon::execution::processing_unit *cpu,
                                                        const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<fetch_indirect_pointer<true>>(),
	        make_instruction_step<fetch_indirect_pointer<true>>(),
	        make_instruction_step<I<&instruction_step::fetch_indirect>>(),
	    },
	    disassembler::indirect_x(mnemonic));
}

template<template<void (instruction_step::*fetch)(std::uint8_t &, bool)> class I>
harpoon::execution::instruction indirect_y_read_factory(harpoon::execution::processing_unit *cpu,
                                                        const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_indirect_pointer<false>>(),
	        make_instruction_step<fetch_indirect_pointer<false>>(),
	        make_instruction_step<I<&instruction_step::fetch_indirect_y>>(),
	    },
	    disassembler::indirect_y(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
