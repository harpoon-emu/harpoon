#include "main_window.hh"

#include "../c64.hh"
#include "control_tab.hh"
#include "log_window.hh"
#include "qt_log.hh"

#include "harpoon/exception/hardware_component_exception.hh"

#include <QDockWidget>
#include <QTabWidget>

namespace commodore {
namespace ui {

main_window::main_window(QWidget *parent) : QMainWindow(parent) {

	qRegisterMetaType<harpoon::log::message>("harpoon::log::message");

	_tab_widget = new QTabWidget(this);

	QDockWidget *log_widget = new QDockWidget(tr("Log"), this);
	addDockWidget(Qt::BottomDockWidgetArea, log_widget);

	_log_window = new log_window(log_widget);
	log_widget->setWidget(_log_window);

	_log = std::make_shared<qt_log>();

	QObject::connect(_log->get_signal_emitter(),
	                 SIGNAL(message_logged(const harpoon::log::message &)), _log_window,
	                 SLOT(log_message(const harpoon::log::message &)), Qt::QueuedConnection);

	try {
		_c64 = std::make_shared<commodore::c64>(_log);
		_c64->create();
	} catch (harpoon::exception::hardware_component_exception &error) {
		_log->out(log_critical_c(error.get_component()) << error.what());
	} catch (std::exception &error) {
		_log->out(log_critical << error.what());
	}

	_tab_widget->addTab(new control_tab(_c64), "Control");
	setCentralWidget(_tab_widget);
}

main_window::~main_window() {
	if (_c64->is_running()) {
		_c64->shutdown();
	}
}

} // namespace ui
} // namespace commodore
