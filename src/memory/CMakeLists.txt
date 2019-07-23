set(DIR memory)

set(SOURCE_FILES
	memory.cc
	main_memory.cc
	linear_memory.cc
	chunked_memory.cc
	random_access_memory.cc
	read_only_memory.cc
	linear_random_access_memory.cc
	linear_read_only_memory.cc
	chunked_random_access_memory.cc
	chunked_read_only_memory.cc
	multiplexed_memory.cc
	)

set(INCLUDE_FILES
	address.hh
	address_range.hh
	memory.hh
	main_memory.hh
	linear_memory.hh
	chunked_memory.hh
	random_access_memory.hh
	read_only_memory.hh
	linear_random_access_memory.hh
	linear_read_only_memory.hh
	chunked_random_access_memory.hh
	chunked_read_only_memory.hh
	multiplexed_memory.hh
	io_memory.hh
	)

add_sources()

add_subdirectory(exception)
add_subdirectory(serializer)
add_subdirectory(deserializer)
