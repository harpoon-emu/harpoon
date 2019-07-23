set(DIR src)
set(BASE_INCLUDE_DIR include/harpoon)

set(SOURCE_FILES
	hardware_component.cc
	computer_system.cc
	)

set(INCLUDE_FILES
	harpoon.hh
	hardware_component.hh
	computer_system.hh
	)

add_sources()

add_subdirectory(exception)
add_subdirectory(log)
add_subdirectory(clock)
add_subdirectory(execution)
add_subdirectory(memory)

