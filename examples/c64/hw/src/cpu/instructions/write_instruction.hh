#ifndef CPU_INSTRUCTIONS_WRITE_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_WRITE_INSTRUCTION_HH

#include "../mos_6510.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename T, T (mos_6510::*get_reg)() const, void (instruction_step::*store)(T)>
class store_register : public instruction_step_write {
	using instruction_step_write::instruction_step_write;

	virtual void execute() override {
		(this->*store)((get_cpu()->*get_reg)());
	}
};

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_write_factory(harpoon::execution::processing_unit *cpu,
                                                        const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<I<&instruction_step::store_zero_page>>(),
	    },
	    disassembler::zero_page(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I,
         std::uint8_t (mos_6510::*get_reg)() const, typename D>
harpoon::execution::instruction
zero_page_index_write_factory(harpoon::execution::processing_unit *cpu,
                              const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<I<&instruction_step::store_zero_page_reg<get_reg>>>(),
	    },
	    D(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_x_write_factory(harpoon::execution::processing_unit *cpu,
                                                          const std::string &mnemonic) {
	return zero_page_index_write_factory<I, &mos_6510::get_X, disassembler::zero_page_x>(cpu,
	                                                                                     mnemonic);
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_y_write_factory(harpoon::execution::processing_unit *cpu,
                                                          const std::string &mnemonic) {
	return zero_page_index_write_factory<I, &mos_6510::get_Y, disassembler::zero_page_y>(cpu,
	                                                                                     mnemonic);
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_write_factory(harpoon::execution::processing_unit *cpu,
                                                       const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<I<&instruction_step::store_absolute>>(),
	    },
	    disassembler::absolute(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I,
         std::uint8_t (mos_6510::*get_reg)() const, typename D>
harpoon::execution::instruction
absolute_index_write_factory(harpoon::execution::processing_unit *cpu,
                             const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<I<&instruction_step::store_absolute_reg<get_reg>>>(),
	    },
	    D(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_x_write_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return absolute_index_write_factory<I, &mos_6510::get_X, disassembler::absolute_x>(cpu,
	                                                                                   mnemonic);
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_y_write_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return absolute_index_write_factory<I, &mos_6510::get_Y, disassembler::absolute_y>(cpu,
	                                                                                   mnemonic);
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction indirect_x_write_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<fetch_indirect_pointer<true>>(),
	        make_instruction_step<fetch_indirect_pointer<true>>(),
	        make_instruction_step<I<&instruction_step::store_indirect>>(),
	    },
	    disassembler::indirect_x(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction indirect_y_write_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_indirect_pointer<false>>(),
	        make_instruction_step<fetch_indirect_pointer<false>>(),
	        make_instruction_step<I<&instruction_step::store_indirect_y>>(),
	    },
	    disassembler::indirect_y(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
