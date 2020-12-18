add_executable(
	t_clock_runner
	clock.cc
	)

target_link_libraries(
	t_clock_runner
	gmock_main
	harpoon
	)

add_test(
	NAME
	Harpoon/Clock
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/clock/t_clock_runner
	)

