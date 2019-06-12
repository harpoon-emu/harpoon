#include "harpoon/execution/up_execution_unit.hh"

namespace harpoon {
namespace execution {

up_execution_unit::~up_execution_unit() {}

void up_execution_unit::prepare() {
	execution_unit::prepare();

	get_clock()->schedule(
	    0, 0, [this](hardware_component *trigger) { get_processing_unit()->step(trigger); });
}

} // namespace execution
} // namespace harpoon
