add_executable(
	t_log_runner
	message.cc
	log.cc
	stream_log.cc
	queue_log.cc
	)

target_link_libraries(
	t_log_runner
	gmock_main
	harpoon
	)

add_test(
	NAME
	Harpoon/Log
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/log/t_log_runner
	)


