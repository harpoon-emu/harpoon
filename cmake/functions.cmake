function(check_and_create_file name)
	if(NOT EXISTS "${CURRENT_TARGET_DIR}/${name}")
		file(APPEND "${CURRENT_TARGET_DIR}/${name}" "")
		message(STATUS "Creating file: ${CURRENT_TARGET_DIR}/${name}")
	endif()
endfunction(check_and_create_file)

function(add_sources)

	if(SOURCE_DIR)
		set(SOURCE_DIR ${SOURCE_DIR}/${DIR})
	else()
		set(SOURCE_DIR ${DIR})
	endif()

	if(SOURCE_GROUP)
		set(SOURCE_GROUP ${SOURCE_GROUP}\\${DIR})
	else()
		set(SOURCE_GROUP ${DIR})
	endif()

	if(INCLUDE_DIR)
		set(INCLUDE_DIR ${INCLUDE_DIR}/${DIR})
	else()
		set(INCLUDE_DIR ${BASE_INCLUDE_DIR})
	endif()

	if(INCLUDE_GROUP)
		set(INCLUDE_GROUP ${INCLUDE_GROUP}\\${DIR})
	else()
		set(INCLUDE_GROUP include)
	endif()

	set(lst_src "")
	foreach(f ${SOURCE_FILES})
		list(APPEND lst_src "${SOURCE_DIR}/${f}")
		check_and_create_file("${SOURCE_DIR}/${f}")
	endforeach(f)
	list(APPEND lst_src "${SOURCE_DIR}/CMakeLists.txt")

	set(lst_inc "")
	foreach(f ${INCLUDE_FILES})
		list(APPEND lst_inc "${INCLUDE_DIR}/${f}")
		check_and_create_file(${INCLUDE_DIR}/${f})
	endforeach(f)

	set(SOURCES 
		${SOURCES}
		${lst_src}
		CACHE INTERNAL "SOURCES"
		)

	set(INCLUDES 
		${INCLUDES}
		${lst_inc}
		CACHE INTERNAL "INCLUDES"
		)

	set(SOURCE_GROUPS
		${SOURCE_GROUPS}
		${SOURCE_GROUP}
		${INCLUDE_GROUP}
		CACHE INTERNAL "SOURCE_GROUPS"
		)

	string(REPLACE "\\" "_" SOURCE_GROUP_FILES_VAR "sgf_${SOURCE_GROUP}")
	string(REPLACE "\\" "_" INCLUDE_GROUP_FILES_VAR "sgf_${INCLUDE_GROUP}")
	set(${SOURCE_GROUP_FILES_VAR} ${lst_src} CACHE INTERNAL "${SOURCE_GROUP_FILES_VAR}")
	set(${INCLUDE_GROUP_FILES_VAR} ${lst_inc} CACHE INTERNAL "${INCLUDE_GROUP_FILES_VAR}")
	set(SOURCE_GROUPS_FILES
		${SOURCE_GROUPS_FILES}
		${SOURCE_GROUP_FILES_VAR}
		${INCLUDE_GROUP_FILES_VAR}
		CACHE INTERNAL "SOURCE_GROUPS_FILES"
		)

	set(SOURCE_DIR ${SOURCE_DIR} PARENT_SCOPE)
	set(SOURCE_GROUP ${SOURCE_GROUP} PARENT_SCOPE)
	set(INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)
	set(INCLUDE_GROUP ${INCLUDE_GROUP} PARENT_SCOPE)

endfunction(add_sources)
