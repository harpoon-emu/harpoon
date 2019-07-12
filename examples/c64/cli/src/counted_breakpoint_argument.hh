#ifndef C64_CLI_COUNTED_BREAKPOINT_ARGUMENT_HH
#define C64_CLI_COUNTED_BREAKPOINT_ARGUMENT_HH

#include "integer.hh"

#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <iomanip>
#include <iostream>
#include <string>

namespace c64 {
namespace cli {

struct counted_breakpoint_argument {
	counted_breakpoint_argument(const integer<std::uint16_t> &a, std::uint32_t c)
	    : address(a), count(c) {}

	integer<std::uint16_t> address;
	std::uint32_t count;
};

template<class CharType, class Traits>
static void validate(boost::any &v, const std::vector<std::basic_string<CharType, Traits>> &xs,
                     counted_breakpoint_argument *, int) {

	boost::program_options::validators::check_first_occurrence(v);
	const std::string &s = boost::program_options::validators::get_single_string(xs);

	boost::regex r("^((\\$|0x)([0-9a-fA-F]{1,4})):([0-9]+)$");
	boost::smatch match;
	if (boost::regex_match(s, match, r)) {
		c64::cli::integer<std::uint16_t> a;
		a.parse(static_cast<std::string>(match[1]));
		v = boost::any(
		    counted_breakpoint_argument(a, boost::lexical_cast<std::uint32_t>(match[4])));
	} else {
		throw boost::program_options::validation_error(
		    boost::program_options::validation_error::invalid_option_value);
	}
}

} // namespace cli
} // namespace c64

#endif
