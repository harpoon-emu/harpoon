#ifndef HARPOON_HARDWARE_COMPONENT_HH
#define HARPOON_HARDWARE_COMPONENT_HH

#include "harpoon/harpoon.hh"
#include "harpoon/log/log.hh"

#include <list>
#include <atomic>

namespace harpoon {

class hardware_component;

using hardware_component_ptr = std::shared_ptr<hardware_component>;
using hardware_component_weak_ptr = std::weak_ptr<hardware_component>;

class hardware_component : public std::enable_shared_from_this<hardware_component> {
public:

	hardware_component(const std::string& name = {}) : _name(name) {}

	hardware_component(const hardware_component&) = default;

	hardware_component& operator=(const hardware_component&) = default;

	virtual ~hardware_component();

	const std::string& get_name() const {
		return _name;
	}

	void set_name(const std::string& name) {
		_name = name;
	}

	hardware_component_ptr get_parent_component() const {
		return _parent_component.lock();
	}

	void add_component(const hardware_component_ptr& component);

	void replace_component(const hardware_component_weak_ptr& old_component,
						   const hardware_component_ptr& new_component);

	void set_log(const log::log_ptr& log) {
		_log = log;
	}

	const log::log_ptr& get_log() const;

	void log(const std::ostream& stream) const;

	virtual void prepare();
	virtual void cleanup();

	virtual void boot();
	virtual void shutdown();

	bool is_running() const {
		return _running;
	}

private:
	void set_parent_component(const hardware_component_ptr& parent_component) {
		_parent_component = parent_component;
	}

	std::string _name{};
	hardware_component_weak_ptr _parent_component{};
	std::list<hardware_component_ptr> _components{};
	log::log_ptr _log{};
	std::atomic_bool _running{false};
};

#define component_critical (log_debug_c(get_name()))
#define component_error (log_error_c(get_name()))
#define component_warning (log_warning_c(get_name()))
#define component_notice (log_notice_c(get_name()))
#define component_debug (log_debug_c(get_name()))

}

#endif