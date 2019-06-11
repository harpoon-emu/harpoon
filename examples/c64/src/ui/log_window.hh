#ifndef UI_LOG_WINDOW_HH
#define UI_LOG_WINDOW_HH

#include "harpoon/log/message.hh"

#include <QTextEdit>

namespace commodore {
namespace ui {

class log_window : public QTextEdit {
	Q_OBJECT

public:
	log_window(QWidget *parent);

public slots:
	void log_message(const harpoon::log::message &message);
};

} // namespace ui
} // namespace commodore

#endif
