set(DIR hw)

set(SOURCE_FILES
	c64.cc
	)

set(INCLUDE_FILES
	c64.hh
	)

add_sources()

add_subdirectory(cpu)
add_subdirectory(memory)
