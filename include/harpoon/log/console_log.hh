#ifndef HARPOON_LOG_CONSOLE_LOG_HH
#define HARPOON_LOG_CONSOLE_LOG_HH

#include "harpoon/harpoon.hh"

#include "harpoon/log/stream_log.hh"

#include <iostream>
#include <mutex>

namespace harpoon {
namespace log {

class console_log : public stream_log {
public:
	console_log() : stream_log(std::cout) {}

	virtual ~console_log();
};

using console_log_ptr = std::shared_ptr<console_log>;

template<typename... Args>
console_log_ptr make_console_log(Args &&... args) {
	return std::make_shared<console_log>(std::forward<Args>(args)...);
}

} // namespace log
} // namespace harpoon

#endif
