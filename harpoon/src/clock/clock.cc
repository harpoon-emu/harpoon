#include "harpoon/clock/clock.hh"

using namespace harpoon::clock;

clock::~clock() {}

void clock::boot() {
	_generator->start();
	hardware_component::boot();
}

void clock::shutdown() {
	_generator->stop();
	hardware_component::shutdown();
}
