#include "control_tab.hh"

#include "c64.hh"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

namespace c64 {
namespace ui {

control_tab::control_tab(const std::shared_ptr<hw::c64> &c64, QWidget *parent) : QWidget(parent) {

	_c64 = c64;

	QHBoxLayout *hbox = new QHBoxLayout();
	_boot_btn = new QPushButton("&Boot");
	_shutdown_btn = new QPushButton("&Shutdown");
	_dump_state_btn = new QPushButton("&Dump state");

	hbox->addWidget(_boot_btn);
	hbox->addWidget(_shutdown_btn);
	hbox->addWidget(_dump_state_btn);

	setLayout(hbox);

	connect(_boot_btn, SIGNAL(released()), this, SLOT(boot()));
	connect(_shutdown_btn, SIGNAL(released()), this, SLOT(shutdown()));
	connect(_dump_state_btn, SIGNAL(released()), this, SLOT(dump_state()));

	update_buttons();
}

void control_tab::boot() {
	_c64->prepare();
	_c64->boot();

	_thread.reset(new std::thread([this] { _c64->run(); }));

	update_buttons();
}

void control_tab::shutdown() {
	if (_c64->is_running()) {
		_c64->shutdown();
		if (_thread) {
			_thread->join();
			_thread.reset();
		}
	}
	update_buttons();
}

void control_tab::dump_state() {
	_c64->log_state();
}

void control_tab::update_buttons() {
	_boot_btn->setEnabled(!_c64->is_running());
	_shutdown_btn->setEnabled(_c64->is_running());
}

} // namespace ui
} // namespace c64
