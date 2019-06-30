#include "mos_6510.hh"

#include "instructions/mos_6510.hh"

#include "harpoon/execution/exception/invalid_instruction.hh"

namespace c64 {
namespace hw {
namespace cpu {

mos_6510::~mos_6510() {}

void mos_6510::create() {
	create_zero_page();

	init_instructions();
}

void mos_6510::create_zero_page() {
	auto zp = harpoon::memory::make_io_memory<harpoon::memory::linear_random_access_memory>(
	    "ZPG $0000", harpoon::memory::address_range{0x0000, 0x00FF});
	add_component(zp);
	_zero_page = zp;

	zp->add_out_port(0x01, std::bind(&mos_6510::_zp_01_processor_port_out, this,
	                                 std::placeholders::_1, std::placeholders::_2));
}

void mos_6510::init_registers() {
	_registers.A = 0xaa;
	_registers.X = 0;
	_registers.Y = 0;
	_registers.PC = 0;
	_registers.SP = 0;
	_registers.IR = 0;
	_registers.SP--;
	_registers.SP--;
	_registers.SP--;
}

void mos_6510::init_zero_page() {
	auto zp = _zero_page.lock();
	std::map<harpoon::memory::address, std::uint8_t> data = {{0x00, 0x2F}, {0x01, 0x37}};

	for (auto &cell : data) {
		zp->set(cell.first, cell.second);
	}
}

void mos_6510::init_instructions() {
	register_instruction_factory<instructions::adc::immediate>();
	register_instruction_factory<instructions::adc::zero_page>();
	register_instruction_factory<instructions::adc::zero_page_x>();
	register_instruction_factory<instructions::adc::absolute>();
	register_instruction_factory<instructions::adc::absolute_x>();
	register_instruction_factory<instructions::adc::absolute_y>();
	register_instruction_factory<instructions::adc::indirect_x>();
	register_instruction_factory<instructions::adc::indirect_y>();
	register_instruction_factory<instructions::and_::immediate>();
	register_instruction_factory<instructions::and_::zero_page>();
	register_instruction_factory<instructions::and_::zero_page_x>();
	register_instruction_factory<instructions::and_::absolute>();
	register_instruction_factory<instructions::and_::absolute_x>();
	register_instruction_factory<instructions::and_::absolute_y>();
	register_instruction_factory<instructions::and_::indirect_x>();
	register_instruction_factory<instructions::and_::indirect_y>();
	register_instruction_factory<instructions::asl::accumulator>();
	register_instruction_factory<instructions::asl::zero_page>();
	register_instruction_factory<instructions::asl::zero_page_x>();
	register_instruction_factory<instructions::asl::absolute>();
	register_instruction_factory<instructions::asl::absolute_x>();
	register_instruction_factory<instructions::bcc::relative>();
	register_instruction_factory<instructions::bcs::relative>();
	register_instruction_factory<instructions::beq::relative>();
	register_instruction_factory<instructions::bit::zero_page>();
	register_instruction_factory<instructions::bit::absolute>();
	register_instruction_factory<instructions::bmi::relative>();
	register_instruction_factory<instructions::bne::relative>();
	register_instruction_factory<instructions::bpl::relative>();
	register_instruction_factory<instructions::brk::implied>();
	register_instruction_factory<instructions::bvc::relative>();
	register_instruction_factory<instructions::bvs::relative>();
	register_instruction_factory<instructions::clc::implied>();
	register_instruction_factory<instructions::cld::implied>();
	register_instruction_factory<instructions::cli::implied>();
	register_instruction_factory<instructions::clv::implied>();
	register_instruction_factory<instructions::cmp::immediate>();
	register_instruction_factory<instructions::cmp::zero_page>();
	register_instruction_factory<instructions::cmp::zero_page_x>();
	register_instruction_factory<instructions::cmp::absolute>();
	register_instruction_factory<instructions::cmp::absolute_x>();
	register_instruction_factory<instructions::cmp::absolute_y>();
	register_instruction_factory<instructions::cmp::indirect_x>();
	register_instruction_factory<instructions::cmp::indirect_y>();
	register_instruction_factory<instructions::cpx::immediate>();
	register_instruction_factory<instructions::cpx::zero_page>();
	register_instruction_factory<instructions::cpx::absolute>();
	register_instruction_factory<instructions::cpy::immediate>();
	register_instruction_factory<instructions::cpy::zero_page>();
	register_instruction_factory<instructions::cpy::absolute>();
	register_instruction_factory<instructions::dec::zero_page>();
	register_instruction_factory<instructions::dec::zero_page_x>();
	register_instruction_factory<instructions::dec::absolute>();
	register_instruction_factory<instructions::dec::absolute_x>();
	register_instruction_factory<instructions::dex::implied>();
	register_instruction_factory<instructions::dey::implied>();
	register_instruction_factory<instructions::eor::immediate>();
	register_instruction_factory<instructions::eor::zero_page>();
	register_instruction_factory<instructions::eor::zero_page_x>();
	register_instruction_factory<instructions::eor::absolute>();
	register_instruction_factory<instructions::eor::absolute_x>();
	register_instruction_factory<instructions::eor::absolute_y>();
	register_instruction_factory<instructions::eor::indirect_x>();
	register_instruction_factory<instructions::eor::indirect_y>();
	register_instruction_factory<instructions::inc::zero_page>();
	register_instruction_factory<instructions::inc::zero_page_x>();
	register_instruction_factory<instructions::inc::absolute>();
	register_instruction_factory<instructions::inc::absolute_x>();
	register_instruction_factory<instructions::inx::implied>();
	register_instruction_factory<instructions::iny::implied>();
	register_instruction_factory<instructions::jmp::absolute>();
	register_instruction_factory<instructions::jmp::indirect>();
	register_instruction_factory<instructions::jsr::absolute>();
	register_instruction_factory<instructions::lda::immediate>();
	register_instruction_factory<instructions::lda::zero_page>();
	register_instruction_factory<instructions::lda::zero_page_x>();
	register_instruction_factory<instructions::lda::absolute>();
	register_instruction_factory<instructions::lda::absolute_x>();
	register_instruction_factory<instructions::lda::absolute_y>();
	register_instruction_factory<instructions::lda::indirect_x>();
	register_instruction_factory<instructions::lda::indirect_y>();
	register_instruction_factory<instructions::ldx::immediate>();
	register_instruction_factory<instructions::ldx::zero_page>();
	register_instruction_factory<instructions::ldx::zero_page_y>();
	register_instruction_factory<instructions::ldx::absolute>();
	register_instruction_factory<instructions::ldx::absolute_y>();
	register_instruction_factory<instructions::ldy::immediate>();
	register_instruction_factory<instructions::ldy::zero_page>();
	register_instruction_factory<instructions::ldy::zero_page_x>();
	register_instruction_factory<instructions::ldy::absolute>();
	register_instruction_factory<instructions::ldy::absolute_x>();
	register_instruction_factory<instructions::lsr::accumulator>();
	register_instruction_factory<instructions::lsr::zero_page>();
	register_instruction_factory<instructions::lsr::zero_page_x>();
	register_instruction_factory<instructions::lsr::absolute>();
	register_instruction_factory<instructions::lsr::absolute_x>();
	register_instruction_factory<instructions::nop::implied>();
	register_instruction_factory<instructions::ora::immediate>();
	register_instruction_factory<instructions::ora::zero_page>();
	register_instruction_factory<instructions::ora::zero_page_x>();
	register_instruction_factory<instructions::ora::absolute>();
	register_instruction_factory<instructions::ora::absolute_x>();
	register_instruction_factory<instructions::ora::absolute_y>();
	register_instruction_factory<instructions::ora::indirect_x>();
	register_instruction_factory<instructions::ora::indirect_y>();
	register_instruction_factory<instructions::rol::accumulator>();
	register_instruction_factory<instructions::rol::zero_page>();
	register_instruction_factory<instructions::rol::zero_page_x>();
	register_instruction_factory<instructions::rol::absolute>();
	register_instruction_factory<instructions::rol::absolute_x>();
	register_instruction_factory<instructions::ror::accumulator>();
	register_instruction_factory<instructions::ror::zero_page>();
	register_instruction_factory<instructions::ror::zero_page_x>();
	register_instruction_factory<instructions::ror::absolute>();
	register_instruction_factory<instructions::ror::absolute_x>();
	register_instruction_factory<instructions::pha::implied>();
	register_instruction_factory<instructions::php::implied>();
	register_instruction_factory<instructions::pla::implied>();
	register_instruction_factory<instructions::plp::implied>();
	register_instruction_factory<instructions::rti::implied>();
	register_instruction_factory<instructions::rts::implied>();
	register_instruction_factory<instructions::sbc::immediate>();
	register_instruction_factory<instructions::sbc::zero_page>();
	register_instruction_factory<instructions::sbc::zero_page_x>();
	register_instruction_factory<instructions::sbc::absolute>();
	register_instruction_factory<instructions::sbc::absolute_x>();
	register_instruction_factory<instructions::sbc::absolute_y>();
	register_instruction_factory<instructions::sbc::indirect_x>();
	register_instruction_factory<instructions::sbc::indirect_y>();
	register_instruction_factory<instructions::sec::implied>();
	register_instruction_factory<instructions::sed::implied>();
	register_instruction_factory<instructions::sei::implied>();
	register_instruction_factory<instructions::sta::zero_page>();
	register_instruction_factory<instructions::sta::zero_page_x>();
	register_instruction_factory<instructions::sta::absolute>();
	register_instruction_factory<instructions::sta::absolute_x>();
	register_instruction_factory<instructions::sta::absolute_y>();
	register_instruction_factory<instructions::sta::indirect_x>();
	register_instruction_factory<instructions::sta::indirect_y>();
	register_instruction_factory<instructions::stx::zero_page>();
	register_instruction_factory<instructions::stx::zero_page_y>();
	register_instruction_factory<instructions::stx::absolute>();
	register_instruction_factory<instructions::sty::zero_page>();
	register_instruction_factory<instructions::sty::zero_page_x>();
	register_instruction_factory<instructions::sty::absolute>();
	register_instruction_factory<instructions::tax::implied>();
	register_instruction_factory<instructions::tay::implied>();
	register_instruction_factory<instructions::tsx::implied>();
	register_instruction_factory<instructions::txa::implied>();
	register_instruction_factory<instructions::txs::implied>();
	register_instruction_factory<instructions::tya::implied>();
}

template<typename T>
void mos_6510::register_instruction_factory() {
	_instruction_factories[T::OPCODE] = T::factory;
	log(component_debug << "Registered instruction with opcode 0x" << std::hex << std::setfill('0')
	                    << std::setw(2) << static_cast<std::uint32_t>(T::OPCODE));
}

void mos_6510::boot() {
	harpoon::execution::processing_unit::boot();
	init_zero_page();
	init_registers();

	_boot_sequence = true;
}

void mos_6510::step(hardware_component *trigger) {
	harpoon::clock::clock *clock = reinterpret_cast<harpoon::clock::clock *>(trigger);

	if (_boot_sequence) {
		boot_sequence();
		clock->schedule(9, 0, [this](harpoon::hardware_component *t) { step(t); });
		return;
	}

	std::uint32_t delay;
	if (get_current_instruction().done() && !_opcode_ready) {
		// No prefetch on last cycle of previous instruction
		// Do fetch opcode and wait 1 cycle.
		fetch_opcode();
		delay = 1;
	} else {
		if (get_current_instruction().done()) {
			// Opcode prefetched on last cycle.
			// Do decode and start execution.
			decode_instruction();
		}
		delay = execute_instruction();
	}

	clock->schedule(delay, 0, [this](harpoon::hardware_component *t) { step(t); });
}

void mos_6510::boot_sequence() {
	auto memory = get_memory();
	memory->get(RESET_VECTOR, _registers.PC);
	fetch_opcode();
	decode_instruction();

	_boot_sequence = false;
}

void mos_6510::decode_instruction() {
	auto factory = _instruction_factories[_registers.IR];
	if (!factory) {
		throw COMPONENT_EXCEPTION0(harpoon::execution::exception::invalid_instruction);
	}

	set_current_instruction(factory(this));
	_opcode_ready = false;
}

void mos_6510::fetch_opcode() {
	_prev_IR = _registers.IR;
	get_program_code(_registers.IR);
	_opcode_ready = true;
}

void mos_6510::get_program_code(std::uint8_t &b) {
	get_memory()->get(_registers.PC, b);
	_registers.PC++;
}

void mos_6510::internal_read(harpoon::memory::address address) {
	_internal_memory_access.b.previous = _internal_memory_access.b.current;
	get_memory()->get(address, _internal_memory_access.b.current);
}

void mos_6510::internal_read_program_code() {
	_internal_memory_access.b.previous = _internal_memory_access.b.current;
	get_program_code(_internal_memory_access.b.current);
}

void mos_6510::fetch_indirect_pointer(bool x_index) {
	std::uint8_t v;
	std::uint8_t index = 0;
	if (x_index) {
		index = _registers.X;
	}
	get_memory()->get((_internal_memory_access.b.current + index) & 0xFF, v);
	_indirect_pointer >>= 8;
	_indirect_pointer |= (static_cast<std::uint16_t>(v) << 8);
	_internal_memory_access.b.current++;
}

void mos_6510::stack_push(std::uint8_t v) {
	get_memory()->set(mos_6510::STACK_ADDRESS + _registers.SP, v);
	_registers.SP--;
}

void mos_6510::stack_pull(std::uint8_t &v) {
	_registers.SP++;
	get_memory()->get(mos_6510::STACK_ADDRESS + _registers.SP, v);
}

void mos_6510::log_registers(harpoon::log::message::Level level) const {
	log(component_log(level) << "A:  " << _registers.A << "    X: " << _registers.X
	                         << "  Y: " << _registers.Y);
	log(component_log(level) << "PC: " << _registers.PC << " SP: " << _registers.SP
	                         << " IR: " << _registers.IR);
	log(component_log(level) << "P:  " << _registers.P);
}

void mos_6510::_zp_01_processor_port_out(const harpoon::memory::address &, std::uint8_t value) {
	get_memory()->switch_d000_dfff(value & 7);
}

} // namespace cpu
} // namespace hw
} // namespace c64
