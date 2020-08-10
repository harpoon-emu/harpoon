#include "harpoon/hardware_component.hh"

#include "harpoon/exception/component_loop.hh"
#include "harpoon/exception/not_subcomponent.hh"
#include "harpoon/exception/subcomponent_owned.hh"
#include "harpoon/exception/wrong_state.hh"
#include "harpoon/log/message.hh"

#include <algorithm>

namespace harpoon {

std::ostream &operator<<(std::ostream &stream, const hardware_component::state &state) {
	std::ostream out(stream.rdbuf());
	out << "[P: " << state.is_prepared() << ", R: " << state.is_running() << "]";
	return stream;
}

hardware_component::~hardware_component() {
	log(component_debug << "Destroying");
}

bool hardware_component::has_subcomponent(const hardware_component_cptr &c, bool deep) const {
	bool direct = std::find(_components.begin(), _components.end(), c) != _components.end();
	if (direct || !deep)
		return direct;

	for (auto s : _components) {
		bool b = s->has_subcomponent(c, true);
		if (b)
			return true;
	}

	return false;
}

bool hardware_component::is_subcomponent_of(const hardware_component_cptr &p, bool deep) const {
	return get_parent_component() == p
	       || (deep && get_parent_component() != nullptr
	           && get_parent_component()->is_subcomponent_of(p, true));
}

void hardware_component::add_component(const hardware_component_ptr &component) {
	if (component->has_parent_component()) {
		throw COMPONENT_EXCEPTION(exception::subcomponent_owned, component);
	}
	if (component == shared_from_this() || is_subcomponent_of(component, true)) {
		throw COMPONENT_EXCEPTION(exception::component_loop, component);
	}

	_components.push_back(component);
	component->set_parent_component(shared_from_this());

	log(component_debug << "Adding component: " << component->get_name());
}

void hardware_component::remove_component(const hardware_component_ptr &component) {
	if (!has_subcomponent(component)) {
		throw COMPONENT_EXCEPTION(exception::not_subcomponent, component);
	}

	_components.remove(component);
	component->set_parent_component(hardware_component_ptr{});

	log(component_debug << "Removing component: " << component->get_name());
}

void hardware_component::replace_component(const hardware_component_ptr &old_component,
                                           const hardware_component_ptr &new_component) {
	if (!has_subcomponent(old_component)) {
		throw COMPONENT_EXCEPTION(exception::not_subcomponent, old_component);
	}
	if (new_component->has_parent_component()) {
		throw COMPONENT_EXCEPTION(exception::subcomponent_owned, new_component);
	}
	if (new_component == shared_from_this() || is_subcomponent_of(new_component, true)) {
		throw COMPONENT_EXCEPTION(exception::component_loop, new_component);
	}

	remove_component(old_component);
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
	if (is_prepared()) {
		throw COMPONENT_EXCEPTION(exception::wrong_state, get_state(), state(false, false));
	}
	log(component_notice << "Preparing");
	for (auto &component : _components) {
		component->prepare();
	}
	_state.set_prepared();
}

void hardware_component::cleanup() {
	if (is_running() || !is_prepared()) {
		throw COMPONENT_EXCEPTION(exception::wrong_state, get_state(), state(true, false));
	}
	log(component_notice << "Cleanup");
	for (auto &component : _components) {
		component->cleanup();
	}
	_state.clear_prepared();
}

void hardware_component::boot() {
	if (!is_prepared() || is_running()) {
		throw COMPONENT_EXCEPTION(exception::wrong_state, get_state(), state(true, false));
	}
	log(component_notice << "Booting");
	for (auto &component : _components) {
		component->boot();
	}
	_state.set_running();
}

void hardware_component::step(hardware_component *) {}

void hardware_component::shutdown() {
	if (!is_running()) {
		throw COMPONENT_EXCEPTION(exception::wrong_state, get_state(), state(true, true));
	}
	log(component_notice << "Shutdown");
	_state.clear_running();
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
