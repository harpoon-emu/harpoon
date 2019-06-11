#ifndef CPU_MOS_6510_DECODER_HH
#define CPU_MOS_6510_DECODER_HH

#include "mos_6510.hh"

#include "harpoon/execution/instruction.hh"
#include "harpoon/execution/instruction_decoder.hh"
#include "harpoon/hardware_component.hh"

#include <array>

namespace commodore {
namespace cpu {

class mos_6510_decoder : public harpoon::hardware_component {
public:
	mos_6510_decoder(mos_6510 *cpu, const std::string &name = {});

	virtual void prepare();

	std::uint_fast64_t decode(harpoon::execution::instruction_handler &instruction_handler,
	                          harpoon::execution::disassemble_handler &disassemble_handler);

	virtual ~mos_6510_decoder();

	std::uint8_t get_instruction_byte(std::uint_fast64_t offset);

	template<typename T>
	void get_program_code(T &data, std::uint_fast64_t offset) {
		const auto &memory = _cpu->get_memory();
		memory->get(_cpu->get_PC() + offset, data);
	}

private:
	template<typename T>
	void register_instruction();

	mos_6510 *_cpu;
	std::array<harpoon::execution::instruction_decode_handler<mos_6510>, 256> _instruction_map{};
};

} // namespace cpu
} // namespace commodore

#endif
