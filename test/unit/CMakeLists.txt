add_executable(
	runner
	memory/address.cc
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
		${CMAKE_BINARY_DIR}/test/unit/runner
	)

