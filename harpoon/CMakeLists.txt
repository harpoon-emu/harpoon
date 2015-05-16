set(CURRENT_TARGET_DIR "${PROJECT_SOURCE_DIR}/harpoon")
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

add_library(harpoon 
	${SOURCES}
	${INCLUDES}
	)

include_directories(include)
