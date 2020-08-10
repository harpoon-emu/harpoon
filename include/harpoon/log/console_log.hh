#ifndef HARPOON_LOG_CONSOLE_LOG_HH
#define HARPOON_LOG_CONSOLE_LOG_HH

#include "harpoon/harpoon.hh"

#include "harpoon/log/log.hh"

#include <mutex>

namespace harpoon {
namespace log {

class console_log : public log {
public:
	virtual ~console_log();

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
	bool _display_component{true};
	bool _display_file{false};
	bool _display_line{false};
	bool _display_function{false};
	std::mutex _mutex{};
};

using console_log_ptr = std::shared_ptr<console_log>;

template<typename... Args>
console_log_ptr make_console_log(Args &&... args) {
	return std::make_shared<console_log>(std::forward<Args>(args)...);
}

} // namespace log
} // namespace harpoon

#endif
