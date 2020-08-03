#include "harpoon/hardware_component.hh"

#include "harpoon/exception/not_subcomponent.hh"
#include "harpoon/exception/subcomponent_owned.hh"
#include "harpoon/log/message.hh"

#include <algorithm>

namespace harpoon {

hardware_component::~hardware_component() {
	log(component_debug << "Destroying");
}

bool hardware_component::has_subcomponent(const hardware_component_cptr &c) const {
	return std::find(_components.begin(), _components.end(), c) != _components.end();
}

bool hardware_component::is_subcomponent_of(const hardware_component_cptr &p) const {
	return p->has_subcomponent(shared_from_this());
}

void hardware_component::add_component(const hardware_component_weak_ptr &component) {

	hardware_component_ptr ptr = component.lock();

	if (ptr->has_parent_component()) {
		throw COMPONENT_EXCEPTION(exception::subcomponent_owned, component);
	}

	_components.push_back(ptr);
	ptr->set_parent_component(shared_from_this());

	log(component_debug << "Adding component: " << ptr->get_name());
}

void hardware_component::remove_component(const hardware_component_weak_ptr &component) {

	hardware_component_ptr ptr = component.lock();

	if (!has_subcomponent(ptr)) {
		throw COMPONENT_EXCEPTION(exception::not_subcomponent, component);
	}

	_components.remove(ptr);
	ptr->set_parent_component(hardware_component_weak_ptr{});

	log(component_debug << "Removing component: " << ptr->get_name());
}

void hardware_component::replace_component(const hardware_component_weak_ptr &old_component,
                                           const hardware_component_weak_ptr &new_component) {
	hardware_component_ptr old_ptr = old_component.lock();

	if (!has_subcomponent(old_ptr)) {
		throw COMPONENT_EXCEPTION(exception::not_subcomponent, old_component);
	}
	if (new_component.lock()->has_parent_component()) {
		throw COMPONENT_EXCEPTION(exception::subcomponent_owned, new_component);
	}

	remove_component(old_ptr);
	add_component(new_component);
}

void hardware_component::set_parent_component(const hardware_component_weak_ptr &parent_component) {
	_parent_component = parent_component;
}

const log::log_ptr &hardware_component::get_log() const {
	if (_log) {
		return _log;
	}

	auto parent = get_parent_component();
	if (parent) {
		return parent->get_log();
	}

	return _log;
}

void hardware_component::log(const std::ostream &stream) const {
	auto &log = get_log();
	if (log) {
		get_log()->out(stream);
	}
}

void hardware_component::prepare() {
	log(component_notice << "Preparing");
	for (auto &component : _components) {
		component->prepare();
	}
}

void hardware_component::cleanup() {
	log(component_notice << "Cleanup");
	for (auto &component : _components) {
		component->cleanup();
	}
	_components.clear();
}

void hardware_component::boot() {
	log(component_notice << "Booting");
	for (auto &component : _components) {
		component->boot();
	}
	_running = true;
}

void hardware_component::step(hardware_component *) {}

void hardware_component::shutdown() {
	log(component_notice << "Shutdown");
	_running = false;
	for (auto &component : _components) {
		component->shutdown();
	}
}

void hardware_component::log_state(bool subcomponents, log::message::Level level) const {
	std::lock_guard<std::mutex> _lk(_mutex);
	log_state(level);
	if (subcomponents) {
		for (const auto &component : _components) {
			component->log_state(subcomponents, level);
		}
	}
}

void hardware_component::log_state(log::message::Level level) const {
	if (is_running()) {
		log(component_log(level) << "RUNNING");
	}
}

} // namespace harpoon
