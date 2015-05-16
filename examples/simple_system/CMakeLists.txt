set(CURRENT_TARGET_DIR "${PROJECT_SOURCE_DIR}/examples/simple_system")
set(SOURCES CACHE INTERNAL "SOURCES")
set(INCLUDES CACHE INTERNAL "SOURCES")
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

find_package(Threads REQUIRED)

add_executable(simple_system 
	${SOURCES}
	${INCLUDES}
	)
target_link_libraries(simple_system 
	${CMAKE_THREAD_LIBS_INIT}
	harpoon
	)

include_directories(${PROJECT_SOURCE_DIR}/harpoon/include)

set_property(TARGET simple_system PROPERTY FOLDER "examples")

install (TARGETS simple_system
         RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
