#ifndef HARPOON_EXECUTION_BASIC_REGISTER_HH
#define HARPOON_EXECUTION_BASIC_REGISTER_HH

#include "harpoon/harpoon.hh"

#include <iomanip>
#include <ostream>

namespace harpoon {
namespace execution {

template<typename T>
class basic_register {
public:
	basic_register() {}
	basic_register(const basic_register &) = default;
	basic_register(const T &value) : _value(value) {}
	basic_register &operator=(const basic_register &) = default;
	basic_register &operator=(const T &value) {
		set(value);
		return *this;
	}

	operator const T &() const {
		return _value;
	}

	operator T &() {
		return _value;
	}

	T operator++() {
		return increment();
	}

	T operator++(int) {
		return increment() - 1;
	}

	T operator--() {
		return decrement();
	}

	T operator--(int) {
		return decrement() + 1;
	}

	const T &get() const {
		return _value;
	}

	T &get() {
		return _value;
	}

	void set(const T &value) {
		_value = value;
	}

	T increment() {
		return ++_value;
	}

	T decrement() {
		return --_value;
	}

private:
	T _value{};
};

template<typename T>
inline std::ostream &operator<<(std::ostream &stream, const basic_register<T> &reg) {
	return stream << "[0x" << std::hex << std::setfill('0') << std::setw(sizeof(T) * 2) << reg.get()
	              << "]";
}

template<>
inline std::ostream &operator<<(std::ostream &stream, const basic_register<std::uint8_t> &reg) {
	return stream << "[0x" << std::hex << std::setfill('0') << std::setw(2)
	              << static_cast<std::uint32_t>(reg.get()) << "]";
}

template<typename T>
using basic_register_ptr = std::shared_ptr<basic_register<T>>;

template<typename T>
using basic_register_weak_ptr = std::weak_ptr<basic_register<T>>;

template<typename T, typename... Args>
basic_register_ptr<T> make_basic_register(Args &&... args) {
	return std::make_shared<basic_register<T>>(std::forward<Args>(args)...);
}

} // namespace execution
} // namespace harpoon

#endif
