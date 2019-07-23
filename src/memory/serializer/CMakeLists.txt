set(DIR serializer)

set(SOURCE_FILES
	serializer.cc
	binary_file.cc
	)

set(INCLUDE_FILES
	serializer.hh
	binary_file.hh
	)

add_sources()

add_subdirectory(exception)
