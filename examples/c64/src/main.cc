#include "ui/main_window.hh"

#include <QApplication>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	c64::ui::main_window main_window;
	main_window.show();
	app.exec();
}
