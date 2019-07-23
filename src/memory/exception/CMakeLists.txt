set(DIR exception)

set(SOURCE_FILES
	memory_exception.cc
	access_violation.cc
	read_access_violation.cc
	write_access_violation.cc
	multiplexer_error.cc
	)

set(INCLUDE_FILES
	memory_exception.hh
	access_violation.hh
	read_access_violation.hh
	write_access_violation.hh
	multiplexer_error.hh
	)

add_sources()
