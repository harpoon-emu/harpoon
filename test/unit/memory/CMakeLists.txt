add_executable(
	t_memory_runner
	address.cc
	address_range.cc
	)

target_link_libraries(
	t_memory_runner
	gtest_main
	harpoon
	)

add_test(
	NAME
	Harpoon/Memory
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/memory/t_memory_runner
	)

