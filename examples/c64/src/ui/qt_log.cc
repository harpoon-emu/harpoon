#include "qt_log.hh"

namespace commodore {
namespace ui {

qt_log::~qt_log() {
	delete _emitter;
}

void qt_log::out(const harpoon::log::message &message) {
	_emitter->emit_signal(message);
}

} // namespace ui
} // namespace commodore
