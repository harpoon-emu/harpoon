#include "harpoon/hardware_component.hh"
#include "harpoon/log/message.hh"

using namespace harpoon;

hardware_component::~hardware_component() {
	log(component_debug << "Destroying");
}

void hardware_component::add_component(const hardware_component_ptr& component) {
	_components.push_back(component);
	component->set_parent_component(shared_from_this());

	log(component_debug << "Adding component: " << component->get_name());
}


void hardware_component::replace_component(const hardware_component_weak_ptr& old_component,
										   const hardware_component_ptr& new_component) {
	hardware_component_ptr old_ptr = old_component.lock();
	if (old_ptr) {
		_components.remove(old_ptr);
		old_ptr->set_parent_component(nullptr);
	}
	add_component(new_component);
}

const log::log_ptr& hardware_component::get_log() const {
	if (_log) {
		return _log;
	}

	auto parent = get_parent_component();
	if (parent) {
		return parent->get_log();
	}

	return _log;
}

void hardware_component::log(const std::ostream& stream) const {
	auto& log = get_log();
	if (log) {
		get_log()->out(stream);
	}
}

void hardware_component::prepare() {
	log(component_notice << "Preparing");
	for (auto& component : _components) {
		component->prepare();
	}
}

void hardware_component::cleanup() {
	log(component_notice << "Cleanup");
	for (auto& component : _components) {
		component->cleanup();
	}
	_components.clear();
}

void hardware_component::boot() {
	log(component_notice << "Booting");
	for (auto& component : _components) {
		component->boot();
	}
	_running = true;
}

void hardware_component::shutdown() {
	log(component_notice << "Shutdown");
	_running = false;
	for (auto& component : _components) {
		component->shutdown();
	}
}
