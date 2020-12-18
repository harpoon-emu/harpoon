#ifndef HARPOON_LOG_STREAM_LOG_HH
#define HARPOON_LOG_STREAM_LOG_HH

#include "harpoon/harpoon.hh"

#include "harpoon/log/log.hh"

#include <mutex>

namespace harpoon {
namespace log {

class stream_log : public log {
public:
	stream_log(std::ostream &stream) : _stream{stream} {}

	virtual ~stream_log();

	using log::out;
	virtual void out(const message &message);

	void display_component(bool display = true) {
		_display_component = display;
	}

	void display_file(bool display = true) {
		_display_file = display;
	}

	void display_line(bool display = true) {
		_display_line = display;
	}

	void display_function(bool display = true) {
		_display_function = display;
	}

private:
	std::ostream &_stream;

	bool _display_component{true};
	bool _display_file{false};
	bool _display_line{false};
	bool _display_function{false};
	std::mutex _mutex{};
};

using stream_log_ptr = std::shared_ptr<stream_log>;

template<typename... Args>
stream_log_ptr make_stream_log(Args &&... args) {
	return std::make_shared<stream_log>(std::forward<Args>(args)...);
}

} // namespace log
} // namespace harpoon

#endif
