#ifndef C64_HH
#define C64_HH

#include "harpoon/computer_system.hh"
#include "harpoon/log/log.hh"
#include "harpoon/memory/memory.hh"

#include <thread>

namespace commodore {

class c64 : public harpoon::computer_system {
public:
	c64(const harpoon::log::log_ptr &log);

	virtual ~c64() override;

	void create();

	virtual void prepare() override;
	virtual void boot() override;
	virtual void shutdown() override;

private:
	void create_execution_unit();
	void create_memory();

	std::unique_ptr<std::thread> _thread{};
};

} // namespace commodore

#endif
