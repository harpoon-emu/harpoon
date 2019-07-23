function(add_sources)

	if(SOURCE_DIR)
		set(SOURCE_DIR ${SOURCE_DIR}/${DIR})
	else()
		set(SOURCE_DIR ${DIR})
	endif()

	if(INCLUDE_DIR)
		set(INCLUDE_DIR ${INCLUDE_DIR}/${DIR})
	else()
		set(INCLUDE_DIR ${BASE_INCLUDE_DIR})
	endif()

	set(lst_src "")
	foreach(f ${SOURCE_FILES})
		list(APPEND lst_src "${SOURCE_DIR}/${f}")
	endforeach(f)
	list(APPEND lst_src "${SOURCE_DIR}/CMakeLists.txt")

	set(lst_inc "")
	foreach(f ${INCLUDE_FILES})
		list(APPEND lst_inc "${INCLUDE_DIR}/${f}")
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

	set(SOURCE_DIR ${SOURCE_DIR} PARENT_SCOPE)
	set(INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)

endfunction(add_sources)
