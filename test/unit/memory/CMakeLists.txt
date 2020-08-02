add_executable(
	runner
	address.cc
	address_range.cc
	)

target_link_libraries(
	runner
	gtest_main
	harpoon
	)

add_test(
	NAME
		unit
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/memory/runner
	)

