#ifndef C64_HH
#define C64_HH

#include "harpoon/computer_system.hh"
#include "harpoon/log/log.hh"
#include "harpoon/memory/memory.hh"

#include <thread>

namespace c64 {
namespace hw {

class c64 : public harpoon::computer_system {
public:
	c64(const harpoon::log::log_ptr &log);

	virtual ~c64() override;

	void enable_flat_memory() {
		_flat_memory = true;
	}

	void create();

private:
	void create_execution_unit();
	void create_memory();

	bool _flat_memory{false};
};

} // namespace hw
} // namespace c64

#endif
