add_subdirectory(log)
add_subdirectory(memory)
add_subdirectory(clock)

add_executable(
	t_runner
	hardware_component.cc
	computer_system.cc
	)

target_link_libraries(
	t_runner
	gmock_main
	harpoon
	)

add_test(
	NAME
		Harpoon
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/t_runner
	)

