#ifndef C64_CLI_LOAD_ARGUMENT_HH
#define C64_CLI_LOAD_ARGUMENT_HH

#include "integer.hh"

#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <iomanip>
#include <iostream>
#include <string>

namespace c64 {
namespace cli {

struct load_argument {
	load_argument(const integer<std::uint16_t> &a, const std::string &f) : address(a), file(f) {}

	integer<std::uint16_t> address;
	std::string file;
};

template<class CharType, class Traits>
static void validate(boost::any &v, const std::vector<std::basic_string<CharType, Traits>> &xs,
                     load_argument *, int) {

	boost::program_options::validators::check_first_occurrence(v);
	const std::string &s = boost::program_options::validators::get_single_string(xs);

	boost::regex r("^(.*):((\\$|0x)([0-9a-fA-F]{1,4}))$");
	boost::smatch match;
	if (boost::regex_match(s, match, r)) {
		c64::cli::integer<std::uint16_t> a;
		a.parse(static_cast<std::string>(match[2]));
		v = boost::any(load_argument(a, match[1]));
	} else {
		throw boost::program_options::validation_error(
		    boost::program_options::validation_error::invalid_option_value);
	}
}

} // namespace cli
} // namespace c64

#endif
