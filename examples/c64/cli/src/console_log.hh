#ifndef CONSOLE_LOG_HH
#define CONSOLE_LOG_HH

#include "harpoon/log/log.hh"

namespace c64 {
namespace cli {

class console_log : public harpoon::log::log {
public:
	console_log() {}

	virtual ~console_log();

	using log::out;
	virtual void out(const harpoon::log::message &message);
};

} // namespace cli
} // namespace c64

#endif
