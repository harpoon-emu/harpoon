set(DIR clock)

set(SOURCE_FILES
	clock.cc
	)

set(INCLUDE_FILES
	tick.hh
	clock.hh
	)

add_sources()

add_subdirectory(generator)
