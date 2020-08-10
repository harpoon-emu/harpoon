#ifndef HARPOON_EXECUTION_UP_EXECUTION_UNIT_HH
#define HARPOON_EXECUTION_UP_EXECUTION_UNIT_HH

#include "harpoon/harpoon.hh"

#include "harpoon/execution/execution_unit.hh"
#include "harpoon/execution/processing_unit.hh"

namespace harpoon {
namespace execution {

class up_execution_unit : public execution_unit {
public:
	using execution_unit::execution_unit;

	void set_processing_unit(const processing_unit_ptr &processing_unit) {
		replace_component(_processing_unit, processing_unit);
		_processing_unit = processing_unit;
	}

	const processing_unit_ptr &get_processing_unit() const {
		return _processing_unit;
	}

	virtual void prepare() override;

	virtual void enable_disassemble() override;
	virtual void disable_disassemble() override;

	virtual ~up_execution_unit() override;

private:
	processing_unit_ptr _processing_unit{};
};

using up_execution_unit_ptr = std::shared_ptr<up_execution_unit>;

template<typename... Args>
up_execution_unit_ptr make_up_execution_unit(Args &&... args) {
	return std::make_shared<up_execution_unit>(std::forward<Args>(args)...);
}

} // namespace execution
} // namespace harpoon

#endif
