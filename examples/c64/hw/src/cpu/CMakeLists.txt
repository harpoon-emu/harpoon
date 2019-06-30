set(DIR cpu)

set(SOURCE_FILES
	mos_6510.cc
	)

set(INCLUDE_FILES
	mos_6510_flags.hh
	mos_6510.hh
	)

add_sources()

add_subdirectory(instructions)
