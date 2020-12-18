#ifndef HARPOON_LOG_QUEUE_LOG_HH
#define HARPOON_LOG_QUEUE_LOG_HH

#include "harpoon/harpoon.hh"

#include "harpoon/log/log.hh"

#include <deque>
#include <mutex>

namespace harpoon {
namespace log {

class queue_log : public log {
public:
	queue_log() {}

	virtual ~queue_log();

	using log::out;
	virtual void out(const message &message);

	bool empty() const;

	message pop();
	void clear();

private:
	std::deque<message> _queue{};

	std::mutex _mutex{};
};

using queue_log_ptr = std::shared_ptr<queue_log>;

template<typename... Args>
queue_log_ptr make_queue_log(Args &&... args) {
	return std::make_shared<queue_log>(std::forward<Args>(args)...);
}

} // namespace log
} // namespace harpoon

#endif
