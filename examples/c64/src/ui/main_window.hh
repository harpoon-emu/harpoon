#ifndef UI_MAIN_WINDOW_HH
#define UI_MAIN_WINDOW_HH

#include <QMainWindow>
#include <memory>

QT_FORWARD_DECLARE_CLASS(QTabWidget)

namespace c64 {

namespace hw {

class c64;

} // namespace hw

namespace ui {

class log_window;
class qt_log;

class main_window : public QMainWindow {
	Q_OBJECT

	QTabWidget *_tab_widget;
	log_window *_log_window;
	std::shared_ptr<qt_log> _log;
	std::shared_ptr<hw::c64> _c64;

public:
	main_window(QWidget *parent = nullptr);

	virtual ~main_window();
};

} // namespace ui
} // namespace c64

#endif
