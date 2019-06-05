#ifndef HARPOON_EXCEPTION_HARPOON_EXCEPTION_HH
#define HARPOON_EXCEPTION_HARPOON_EXCEPTION_HH

#include "harpoon/harpoon.hh"

#include <stdexcept>

namespace harpoon {
namespace exception {

class harpoon_exception : public std::runtime_error {
public:

	harpoon_exception(const std::string& what,
					  const std::string& file = {},
					  int line = {},
					  const std::string& function = {})
		: std::runtime_error(what), _what(what), _file(file), _line(line), _function(function) {}

	harpoon_exception(const harpoon_exception&) = default;
	harpoon_exception& operator=(const harpoon_exception&) = default;

	void set_what(const std::string& what) {
		_what = what;
	}

	const std::string& get_what() const {
		return _what;
	}

	virtual const char* what() const noexcept(true);

	virtual ~harpoon_exception();

private:
	std::string _what{};
	std::string _file{};
	int _line{};
	std::string _function{};
};

template<typename Exception, typename... Args>
Exception make_harpoon_exception(Args&&... args) {
	return Exception(std::forward<Args>(args)...);
}

#define MAKE_HARPOON_EXCEPTION(EXCEPTION, ...)	\
	harpoon::exception::make_harpoon_exception<EXCEPTION>(__VA_ARGS__, __FILE__, __LINE__, __FUNCTION__)

}
}

#endif

