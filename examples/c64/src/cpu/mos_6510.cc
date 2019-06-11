#include "mos_6510.hh"

#include "mos_6510_decoder.hh"

namespace commodore {
namespace cpu {

mos_6510::~mos_6510() {}

void mos_6510::create() {
	auto decoder = std::make_shared<mos_6510_decoder>(this, "Decoder");
	add_component(decoder);
	_decoder = decoder;

	create_zero_page();
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
}

void mos_6510::init_zero_page() {
	auto zp = _zero_page.lock();
	std::map<harpoon::memory::address, std::uint8_t> data = {{0x00, 0x2F}, {0x01, 0x37}};

	for (auto &cell : data) {
		zp->set(cell.first, cell.second);
	}
}

void mos_6510::boot() {
	init_registers();
	init_zero_page();
	harpoon::execution::processing_unit::boot();
}

std::uint_fast64_t mos_6510::begin_execution() {

	auto memory = get_memory();

	_registers.SP = 0;
	_registers.IR = 0;

	_registers.SP--;
	_registers.SP--;
	_registers.SP--;

	memory->get(RESET_VECTOR, _registers.PC);

	return 9;
}

std::uint_fast64_t
mos_6510::fetch_decode(harpoon::execution::instruction_handler &instruction_handler,
                       harpoon::execution::disassemble_handler &disassemble_handler) {
	return _decoder.lock()->decode(instruction_handler, disassemble_handler);
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
} // namespace commodore
