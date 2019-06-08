#ifndef HARPOON_LOG_MESSAGE_HH
#define HARPOON_LOG_MESSAGE_HH

#include "harpoon/harpoon.hh"

#include <sstream>

namespace harpoon {
namespace log {

class message {
public:

	enum class Level {
		CRITICAL,
		ERROR,
		WARNING,
		NOTICE,
		DEBUG
	};

	class streambuf : public std::stringbuf {
	public:

		streambuf(message& message) : _message(message) {}
		streambuf(const streambuf&) = delete;
		streambuf& operator=(const streambuf&) = delete;

		virtual ~streambuf();

		const message& get_message() const {
			return _message;
		}

	private:
		message& _message;

		friend class message;
	};

	message(Level level = Level::NOTICE,
			const std::string& file = {},
			unsigned int line = {},
			const std::string& function = {},
			const std::string& component = {}) :
		_level(level),
		_file(file),
		_line(line),
		_function(function),
		_component(component) {
		_streambuf = std::make_shared<streambuf>(*this);
		_stream = std::make_shared<std::ostream>(_streambuf.get());
	}

	message(const message&) = default;
	message& operator=(const message&) = default;

	virtual ~message();

	Level get_level() const {
		return _level;
	}

	const std::string& get_file() const {
		return _file;
	}

	unsigned int get_line() const {
		return _line;
	}

	const std::string& get_function() const {
		return _function;
	}

	const std::string& get_component() const {
		return _component;
	}

	std::string get_text() const;

	std::ostream& get_stream() {
		return *(_stream.get());
	}

private:
	Level _level{Level::NOTICE};
	std::string _file{};
	unsigned int _line{};
	std::string _function{};
	std::string _component{};
	std::shared_ptr<streambuf> _streambuf{};
	std::shared_ptr<std::ostream> _stream{};
};

#define harpoon_log(__level) \
	((harpoon::log::message((__level), __FILE__, __LINE__, __FUNCTION__)).get_stream())

#define harpoon_log_c(__level, __component) \
	((harpoon::log::message((__level), __FILE__, __LINE__, __FUNCTION__, (__component))).get_stream())

#define log_critical harpoon_log(harpoon::log::message::Level::CRITICAL)
#define log_critical_c(__component) harpoon_log_c(harpoon::log::message::Level::CRITICAL, __component)
#define log_error harpoon_log(harpoon::log::message::Level::ERROR)
#define log_error_c(__component) harpoon_log_c(harpoon::log::message::Level::ERROR, __component)
#define log_warning harpoon_log(harpoon::log::message::Level::WARNING)
#define log_warning_c(__component) harpoon_log_c(harpoon::log::message::Level::WARNING, __component)
#define log_notice harpoon_log(harpoon::log::message::Level::NOTICE)
#define log_notice_c(__component) harpoon_log_c(harpoon::log::message::Level::NOTICE, __component)
#define log_debug harpoon_log(harpoon::log::message::Level::DEBUG)
#define log_debug_c(__component) harpoon_log_c(harpoon::log::message::Level::DEBUG, __component)

}
}

#endif
