set(CURRENT_TARGET_DIR "${PROJECT_SOURCE_DIR}/examples/c64/hw")
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

add_library(c64-hw 
	${SOURCES}
	${INCLUDES}
	)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set_target_properties(
		c64-hw
		PROPERTIES COMPILE_FLAGS "-Wno-undefined-reinterpret-cast")
endif()

include_directories(${PROJECT_SOURCE_DIR}/harpoon/include)
