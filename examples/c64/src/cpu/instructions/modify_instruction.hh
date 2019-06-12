#ifndef CPU_INSTRUCTIONS_MODIFY_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_MODIFY_INSTRUCTION_HH

#include "../mos_6510.hh"
#include "instruction_step.hh"
#include "read_instruction.hh"

#include <functional>

namespace commodore {
namespace cpu {
namespace instructions {

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_modify_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<load_latch<&instruction_step::fetch_zero_page>>(),
	             make_instruction_step<internal_write>(),
	             make_instruction_step<I<&instruction_step::store_zero_page>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I,
         std::uint8_t (mos_6510::*get_reg)() const>
harpoon::execution::instruction
zero_page_index_modify_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<load_latch<&instruction_step::fetch_zero_page_reg<get_reg>>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_zero_page_reg<get_reg>>>(),
	    });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_modify_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu, {
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<fetch_program_code>(),
	             make_instruction_step<load_latch<&instruction_step::fetch_zero_page>>(),
	             make_instruction_step<internal_write>(),
	             make_instruction_step<I<&instruction_step::store_zero_page>>(),
	         });
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I,
         std::uint8_t (mos_6510::*get_reg)() const>
harpoon::execution::instruction
absolute_index_modify_factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<load_latch<&instruction_step::fetch_absolute_reg<get_reg>>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_absolute_reg<get_reg>>>(),
	    });
}

} // namespace instructions
} // namespace cpu
} // namespace commodore

#endif
