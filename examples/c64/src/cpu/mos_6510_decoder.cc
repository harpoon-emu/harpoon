#include "mos_6510_decoder.hh"

#include "instructions/mos_6510.hh"
#include "mos_6510.hh"

#include "harpoon/execution/exception/invalid_instruction.hh"

namespace commodore {
namespace cpu {

template<typename T>
class mos_6510_instruction_decoder : public harpoon::execution::instruction_decoder<T, mos_6510> {};

mos_6510_decoder::mos_6510_decoder(mos_6510 *cpu, const std::string &name)
    : harpoon::hardware_component(name), _cpu(cpu) {}

mos_6510_decoder::~mos_6510_decoder() {}

template<typename T>
void mos_6510_decoder::register_instruction() {
	_instruction_map[T::OPCODE] = mos_6510_instruction_decoder<T>();
	log(component_debug << "Registered instruction with opcode 0x" << std::hex << std::setfill('0')
	                    << std::setw(2) << static_cast<std::uint32_t>(T::OPCODE));
}

void mos_6510_decoder::prepare() {
	register_instruction<instructions::adc_immediate>();
	register_instruction<instructions::adc_zero_page>();
	register_instruction<instructions::adc_zero_page_x>();
	register_instruction<instructions::adc_absolute>();
	register_instruction<instructions::adc_absolute_x>();
	register_instruction<instructions::adc_absolute_y>();
	register_instruction<instructions::adc_indirect_x>();
	register_instruction<instructions::adc_indirect_y>();
	register_instruction<instructions::and_immediate>();
	register_instruction<instructions::and_zero_page>();
	register_instruction<instructions::and_zero_page_x>();
	register_instruction<instructions::and_absolute>();
	register_instruction<instructions::and_absolute_x>();
	register_instruction<instructions::and_absolute_y>();
	register_instruction<instructions::and_indirect_x>();
	register_instruction<instructions::and_indirect_y>();
	register_instruction<instructions::asl_accumulator>();
	register_instruction<instructions::asl_zero_page>();
	register_instruction<instructions::asl_zero_page_x>();
	register_instruction<instructions::asl_absolute>();
	register_instruction<instructions::asl_absolute_x>();
	register_instruction<instructions::bcc>();
	register_instruction<instructions::bcs>();
	register_instruction<instructions::beq>();
	register_instruction<instructions::bit_zero_page>();
	register_instruction<instructions::bit_absolute>();
	register_instruction<instructions::bmi>();
	register_instruction<instructions::bne>();
	register_instruction<instructions::bpl>();
	register_instruction<instructions::bvc>();
	register_instruction<instructions::bvs>();
	register_instruction<instructions::cld>();
	register_instruction<instructions::clc>();
	register_instruction<instructions::cli>();
	register_instruction<instructions::clv>();
	register_instruction<instructions::cmp_immediate>();
	register_instruction<instructions::cmp_zero_page>();
	register_instruction<instructions::cmp_zero_page_x>();
	register_instruction<instructions::cmp_absolute>();
	register_instruction<instructions::cmp_absolute_x>();
	register_instruction<instructions::cmp_absolute_y>();
	register_instruction<instructions::cmp_indirect_x>();
	register_instruction<instructions::cmp_indirect_y>();
	register_instruction<instructions::cpx_immediate>();
	register_instruction<instructions::cpx_zero_page>();
	register_instruction<instructions::cpx_absolute>();
	register_instruction<instructions::cpy_immediate>();
	register_instruction<instructions::cpy_zero_page>();
	register_instruction<instructions::cpy_absolute>();
	register_instruction<instructions::dec_zero_page>();
	register_instruction<instructions::dec_zero_page_x>();
	register_instruction<instructions::dec_absolute>();
	register_instruction<instructions::dec_absolute_x>();
	register_instruction<instructions::dex>();
	register_instruction<instructions::dey>();
	register_instruction<instructions::eor_immediate>();
	register_instruction<instructions::eor_zero_page>();
	register_instruction<instructions::eor_zero_page_x>();
	register_instruction<instructions::eor_absolute>();
	register_instruction<instructions::eor_absolute_x>();
	register_instruction<instructions::eor_absolute_y>();
	register_instruction<instructions::eor_indirect_x>();
	register_instruction<instructions::eor_indirect_y>();
	register_instruction<instructions::inc_zero_page>();
	register_instruction<instructions::inc_zero_page_x>();
	register_instruction<instructions::inc_absolute>();
	register_instruction<instructions::inc_absolute_x>();
	register_instruction<instructions::inx>();
	register_instruction<instructions::iny>();
	register_instruction<instructions::jmp_absolute>();
	register_instruction<instructions::jmp_indirect>();
	register_instruction<instructions::jsr>();
	register_instruction<instructions::lda_immediate>();
	register_instruction<instructions::lda_zero_page>();
	register_instruction<instructions::lda_zero_page_x>();
	register_instruction<instructions::lda_absolute>();
	register_instruction<instructions::lda_absolute_x>();
	register_instruction<instructions::lda_absolute_y>();
	register_instruction<instructions::lda_indirect_x>();
	register_instruction<instructions::lda_indirect_y>();
	register_instruction<instructions::ldx_immediate>();
	register_instruction<instructions::ldx_zero_page>();
	register_instruction<instructions::ldx_zero_page_y>();
	register_instruction<instructions::ldx_absolute>();
	register_instruction<instructions::ldx_absolute_y>();
	register_instruction<instructions::ldy_immediate>();
	register_instruction<instructions::ldy_zero_page>();
	register_instruction<instructions::ldy_zero_page_x>();
	register_instruction<instructions::ldy_absolute>();
	register_instruction<instructions::ldy_absolute_x>();
	register_instruction<instructions::lsr_accumulator>();
	register_instruction<instructions::lsr_zero_page>();
	register_instruction<instructions::lsr_zero_page_x>();
	register_instruction<instructions::lsr_absolute>();
	register_instruction<instructions::lsr_absolute_x>();
	register_instruction<instructions::nop>();
	register_instruction<instructions::ora_immediate>();
	register_instruction<instructions::ora_zero_page>();
	register_instruction<instructions::ora_zero_page_x>();
	register_instruction<instructions::ora_absolute>();
	register_instruction<instructions::ora_absolute_x>();
	register_instruction<instructions::ora_absolute_y>();
	register_instruction<instructions::ora_indirect_x>();
	register_instruction<instructions::ora_indirect_y>();
	register_instruction<instructions::pha>();
	register_instruction<instructions::php>();
	register_instruction<instructions::pla>();
	register_instruction<instructions::plp>();
	register_instruction<instructions::rol_accumulator>();
	register_instruction<instructions::rol_zero_page>();
	register_instruction<instructions::rol_zero_page_x>();
	register_instruction<instructions::rol_absolute>();
	register_instruction<instructions::rol_absolute_x>();
	register_instruction<instructions::ror_accumulator>();
	register_instruction<instructions::ror_zero_page>();
	register_instruction<instructions::ror_zero_page_x>();
	register_instruction<instructions::ror_absolute>();
	register_instruction<instructions::ror_absolute_x>();
	register_instruction<instructions::rti>();
	register_instruction<instructions::rts>();
	register_instruction<instructions::sbc_immediate>();
	register_instruction<instructions::sbc_zero_page>();
	register_instruction<instructions::sbc_zero_page_x>();
	register_instruction<instructions::sbc_absolute>();
	register_instruction<instructions::sbc_absolute_x>();
	register_instruction<instructions::sbc_absolute_y>();
	register_instruction<instructions::sbc_indirect_x>();
	register_instruction<instructions::sbc_indirect_y>();
	register_instruction<instructions::sed>();
	register_instruction<instructions::sec>();
	register_instruction<instructions::sei>();
	register_instruction<instructions::sta_zero_page>();
	register_instruction<instructions::sta_zero_page_x>();
	register_instruction<instructions::sta_absolute>();
	register_instruction<instructions::sta_absolute_x>();
	register_instruction<instructions::sta_absolute_y>();
	register_instruction<instructions::sta_indirect_x>();
	register_instruction<instructions::sta_indirect_y>();
	register_instruction<instructions::stx_zero_page>();
	register_instruction<instructions::stx_zero_page_y>();
	register_instruction<instructions::stx_absolute>();
	register_instruction<instructions::sty_zero_page>();
	register_instruction<instructions::sty_zero_page_x>();
	register_instruction<instructions::sty_absolute>();
	register_instruction<instructions::tax>();
	register_instruction<instructions::tay>();
	register_instruction<instructions::tsx>();
	register_instruction<instructions::txa>();
	register_instruction<instructions::txs>();
	register_instruction<instructions::tya>();

	log(component_notice << "Registered " << _instruction_map.size() << " instructions");
}

std::uint_fast64_t
mos_6510_decoder::decode(harpoon::execution::instruction_handler &instruction_handler,
                         harpoon::execution::disassemble_handler &disassemle_handler) {
	std::uint8_t opcode = get_instruction_byte(0);
	std::size_t pc_increment = 0;

	_cpu->get_registers().IR = opcode;

	const auto &decoder = _instruction_map[opcode];
	if (!decoder) {
		throw COMPONENT_EXCEPTION0(harpoon::execution::exception::invalid_instruction);
	}

	auto cycles = decoder(_cpu, instruction_handler, disassemle_handler, pc_increment);

	_cpu->get_registers().PC += static_cast<std::uint16_t>(pc_increment);

	return cycles;
}

std::uint8_t mos_6510_decoder::get_instruction_byte(std::uint_fast64_t offset) {
	std::uint8_t opbyte{};
	get_program_code(opbyte, offset);
	return opbyte;
}

} // namespace cpu
} // namespace commodore
