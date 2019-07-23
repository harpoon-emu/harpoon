#ifndef HARPOON_LOG_LOG_HH
#define HARPOON_LOG_LOG_HH

#include "harpoon/harpoon.hh"

#include "harpoon/log/message.hh"

namespace harpoon {
namespace log {

class message;

class log {
public:
	virtual ~log();

	virtual void out(const message &message) = 0;

	void out(const std::ostream &stream);
};

using log_ptr = std::shared_ptr<log>;
using log_weak_ptr = std::weak_ptr<log>;

} // namespace log
} // namespace harpoon

#endif
