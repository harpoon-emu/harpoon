#ifndef UI_QT_LOG_HH
#define UI_QT_LOG_HH

#include "harpoon/log/log.hh"

#include <QObject>

Q_DECLARE_METATYPE(harpoon::log::message)

namespace c64 {
namespace ui {

class log_window;

class log_signal_emitter : public QObject {
	Q_OBJECT

public:
	void emit_signal(const harpoon::log::message &message) {
		emit message_logged(message);
	}

signals:
	void message_logged(const harpoon::log::message &message);
};


class qt_log : public harpoon::log::log {
public:
	qt_log() {
		_emitter = new log_signal_emitter;
	}

	virtual ~qt_log();

	using log::out;
	virtual void out(const harpoon::log::message &message);

	log_signal_emitter *get_signal_emitter() {
		return _emitter;
	}

private:
	log_signal_emitter *_emitter{};
};

} // namespace ui
} // namespace c64

#endif
