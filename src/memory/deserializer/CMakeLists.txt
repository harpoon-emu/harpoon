set(DIR deserializer)

set(SOURCE_FILES
	deserializer.cc
	binary_file.cc
	)

set(INCLUDE_FILES
	deserializer.hh
	binary_file.hh
	)

add_sources()

add_subdirectory(exception)
