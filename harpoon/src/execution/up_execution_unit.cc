#include "harpoon/execution/up_execution_unit.hh"

namespace harpoon {
namespace execution {

up_execution_unit::~up_execution_unit() {}

void up_execution_unit::prepare() {
	execution_unit::prepare();

	get_clock()->schedule(
	    0, 0, [this](hardware_component *trigger) { get_processing_unit()->step(trigger); });
}

void up_execution_unit::enable_disassemble() {
	get_processing_unit()->enable_disassemble();
}

void up_execution_unit::disable_disassemble() {
	get_processing_unit()->disable_disassemble();
}

} // namespace execution
} // namespace harpoon
