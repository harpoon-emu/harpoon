#ifndef C64_CLI_INTEGER_HH
#define C64_CLI_INTEGER_HH

#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <iomanip>
#include <iostream>

namespace c64 {
namespace cli {

template<typename T>
class integer {
public:
	integer(T val = {}) : _value(val) {}

	operator const T &() const {
		return _value;
	}

	operator T &() {
		return _value;
	}

	friend std::ostream &operator<<(std::ostream &stream, const integer<T> &integer) {
		std::ostream out(stream.rdbuf());
		out << "$";
		out << std::hex << std::setw(sizeof(T) * 2) << std::uppercase << std::setfill('0')
		    << integer._value;
		return stream;
	}

	template<class CharType, class Traits>
	bool parse(const std::basic_string<CharType, Traits> &s) {
		std::stringstream reg_hex;
		reg_hex << "^(\\$|0x)([0-9a-fA-F]{1," << sizeof(T) * 2 << "})$";

		boost::regex r_c64_hex(reg_hex.str());
		boost::regex r_c64_dec("^([0-9]+)$");

		boost::smatch match;
		std::stringstream ss;

		if (boost::regex_match(s, match, r_c64_hex)) {
			ss << std::hex << match[2];
		} else if (boost::regex_match(s, match, r_c64_dec)) {
			ss << std::dec << match[1];
		} else {
			return false;
		}

		ss >> _value;
		return true;
	}

	template<class CharType, class Traits>
	static void validate(boost::any &v, const std::vector<std::basic_string<CharType, Traits>> &xs,
	                     integer<T> *, int) {


		boost::program_options::validators::check_first_occurrence(v);
		const std::basic_string<CharType, Traits> &s
		    = boost::program_options::validators::get_single_string(xs);

		integer<T> i;

		if (!i.parse(s)) {
			throw boost::program_options::validation_error(
			    boost::program_options::validation_error::invalid_option_value);
		}
		v = boost::any(i);
	}

private:
	T _value{};
};

template<class CharType, class Traits>
void validate(boost::any &v, const std::vector<std::basic_string<CharType, Traits>> &xs,
              integer<std::uint8_t> *u1, int u2) {
	integer<std::uint8_t>::validate<CharType, Traits>(v, xs, u1, u2);
}

template<class CharType, class Traits>
void validate(boost::any &v, const std::vector<std::basic_string<CharType, Traits>> &xs,
              integer<std::uint16_t> *u1, int u2) {
	integer<std::uint16_t>::validate<CharType, Traits>(v, xs, u1, u2);
}

} // namespace cli
} // namespace c64

#endif
