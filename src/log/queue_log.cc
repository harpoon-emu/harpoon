#include "harpoon/log/queue_log.hh"

#include "harpoon/log/message.hh"

namespace harpoon {
namespace log {

queue_log::~queue_log() {}

void queue_log::out(const message &message) {
	std::lock_guard<std::mutex> lk(_mutex);
	_queue.push_back(message);
}

bool queue_log::empty() const {
	return _queue.empty();
}

message queue_log::pop() {
	std::lock_guard<std::mutex> lk(_mutex);
	message m = _queue.front();
	_queue.pop_front();
	return m;
}

void queue_log::clear() {
	std::lock_guard<std::mutex> lk(_mutex);
	_queue.clear();
}

} // namespace log
} // namespace harpoon
