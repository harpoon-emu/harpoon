#ifndef CPU_INSTRUCTIONS_WRITE_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_WRITE_INSTRUCTION_HH

#include "../mos_6510.hh"
#include "instruction_step.hh"

#include <functional>

namespace commodore {
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
harpoon::execution::instruction zero_page_write_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<I<&instruction_step::store_zero_page>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I,
         std::uint8_t (mos_6510::*get_reg)() const>
harpoon::execution::instruction
zero_page_index_write_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<internal_read>(),
	             make_instruction_step<I<&instruction_step::store_zero_page_reg<get_reg>>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_write_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<I<&instruction_step::store_absolute>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I,
         std::uint8_t (mos_6510::*get_reg)() const>
harpoon::execution::instruction
absolute_index_write_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<internal_read>(),
	             make_instruction_step<I<&instruction_step::store_absolute_reg<get_reg>>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction indirect_x_write_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<internal_read>(),
	             make_instruction_step<fetch_indirect_pointer<true>>(),
	             make_instruction_step<fetch_indirect_pointer<true>>(),
	             make_instruction_step<I<&instruction_step::store_indirect>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction indirect_y_write_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<fetch_indirect_pointer<false>>(),
	             make_instruction_step<fetch_indirect_pointer<false>>(),
	             make_instruction_step<I<&instruction_step::store_indirect_y>>(),
	         });
}

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
