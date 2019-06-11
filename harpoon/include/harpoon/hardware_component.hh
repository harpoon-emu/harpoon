/**
 * @file hardware_component.hh
 * @brief Hardware component.
 */
#ifndef HARPOON_HARDWARE_COMPONENT_HH
#define HARPOON_HARDWARE_COMPONENT_HH

#include "harpoon/harpoon.hh"

#include "harpoon/log/log.hh"

#include <atomic>
#include <list>
#include <mutex>

namespace harpoon {

class hardware_component;

/** std::shared_ptr pointing to hardware_component object */
using hardware_component_ptr = std::shared_ptr<hardware_component>;

/** std::weak_ptr pointing to hardware_component object */
using hardware_component_weak_ptr = std::weak_ptr<hardware_component>;

/**
 * @brief Base class for all hardware components of computer system (i.e. CPU, memory).
 * All components should derive from this class.
 */
class hardware_component : public std::enable_shared_from_this<hardware_component> {
public:
	/**
	 * @brief Hardware component default constructor.
	 * @param[in] name Hardware component name.
	 */
	hardware_component(const std::string &name = {}) : _name(name) {}

	/**
	 * @brief Default copy constructor.
	 * @param[in] source Source hardware component.
	 */
	hardware_component(const hardware_component &source) = delete;

	/**
	 * @brief Default assignment operator.
	 * @param[in] source Source hardware component.
	 * @return Reference to hardware component.
	 */
	hardware_component &operator=(const hardware_component &source) = delete;

	/**
	 * @brief Destructor.
	 */
	virtual ~hardware_component();

	/**
	 * @brief Add hardware component to components hierarchy.
	 * @param[in] component Child component.
	 */
	void add_component(const hardware_component_weak_ptr &component);

	/**
	 * @brief Remove component from components hierachy.
	 * @param[in] component Component to be removed.
	 */
	void remove_component(const hardware_component_weak_ptr &component);

	/**
	 * @brief Replace component with new component.
	 * @param[in] old_component Component to be replaced.
	 * @param[in] new_component New component.
	 */
	void replace_component(const hardware_component_weak_ptr &old_component,
	                       const hardware_component_weak_ptr &new_component);

	/**
	 * @brief Perform component setup. Called during system preparation stage.
	 */
	virtual void prepare();

	/**
	 * @brief Cleanup component. Called during system cleanup stage.
	 */
	virtual void cleanup();

	/**
	 * @brief Boot component. Called during system startup stage (booting).
	 */
	virtual void boot();

	/**
	 * @brief Shutdown component. Called during system shutdown stage.
	 */
	virtual void shutdown();

	/**
	 * @brief Emit message to component log.
	 * @param[in] stream Stream with log message collected.
	 */
	void log(const std::ostream &stream) const;

	/**
	 * @brief Check is component is running.
	 * @return true if component is running.
	 */
	bool is_running() const {
		return _running;
	}

	/**
	 * @brief Return hardware component name.
	 * @return Hardware component name.
	 */
	const std::string &get_name() const {
		return _name;
	}

	/**
	 * @brief Set hardware component name.
	 * @param[in] name Hardware component name.
	 */
	void set_name(const std::string &name) {
		_name = name;
	}

	/**
	 * @brief Get parent component.
	 * @return Parent component.
	 */
	hardware_component_ptr get_parent_component() const {
		return _parent_component.lock();
	}

	/**
	 * @brief Get hardware component log.
	 * @details If component has no associated log then parent component log is returned.
	 * @return Hardware component log.
	 */
	const log::log_ptr &get_log() const;

	/**
	 * @brief Set hardware component log.
	 * @param[in] log Log.
	 */
	void set_log(const log::log_ptr &log) {
		_log = log;
	}

	/**
	 * @brief Dump state of component to log.
	 * @param[in] subcomponents If true, state of all subcomponents will also be logged.
	 * @param[in] level Log level to be used.
	 */
	virtual void log_state(bool subcomponents = true,
	                       log::message::Level level = log::message::Level::DEBUG) const;

	/**
	 * @brief Dump state of component to log.
	 * @param[in] level Log level to be used.
	 */
	virtual void log_state(log::message::Level level) const;

private:
	void set_parent_component(const hardware_component_weak_ptr &parent_component);

	std::string _name{};
	hardware_component_weak_ptr _parent_component{};
	std::list<hardware_component_ptr> _components{};
	log::log_ptr _log{};
	std::atomic_bool _running{false};
	mutable std::mutex _mutex;
};

#define component_log(__level) (harpoon_log_c(__level, get_name()))
#define component_critical (log_debug_c(get_name()))
#define component_error (log_error_c(get_name()))
#define component_warning (log_warning_c(get_name()))
#define component_notice (log_notice_c(get_name()))
#define component_debug (log_debug_c(get_name()))

} // namespace harpoon

#endif
