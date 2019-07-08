set(CURRENT_TARGET_DIR "${PROJECT_SOURCE_DIR}/examples/c64/cli")
set(SOURCES CACHE INTERNAL "SOURCES")
set(INCLUDES CACHE INTERNAL "INCLUDES")
set(SOURCE_GROUPS CACHE INTERNAL "SOURCE_GROUPS")
set(SOURCE_GROUPS_FILES CACHE INTERNAL "SOURCE_GROUPS_FILES")

add_subdirectory(src)

list(LENGTH SOURCE_GROUPS count)
math(EXPR count "${count}-1")
foreach(i RANGE ${count})
	list(GET SOURCE_GROUPS ${i} group)
	list(GET SOURCE_GROUPS_FILES ${i} group_files_var)
	source_group(${group} FILES ${${group_files_var}})
endforeach()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS program_options regex REQUIRED)

add_executable(c64-cli
	${SOURCES}
	${INCLUDES}
	)
target_link_libraries(c64-cli
	Threads::Threads
	${Boost_LIBRARIES}
	c64-hw
	harpoon
	)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set_target_properties(
		c64-cli
		PROPERTIES COMPILE_FLAGS "-Wno-undefined-reinterpret-cast")
endif()

include_directories(${Boost_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/harpoon/include)
include_directories(${PROJECT_SOURCE_DIR}/examples/c64/hw/src)

set_property(TARGET c64-cli PROPERTY FOLDER "examples")

install (TARGETS c64-cli
         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
