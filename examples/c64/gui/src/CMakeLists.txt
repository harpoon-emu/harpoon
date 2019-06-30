set(DIR src)
set(BASE_INCLUDE_DIR src)

set(SOURCE_FILES
	main.cc
	main_window.cc
	log_window.cc
	control_tab.cc
	qt_log.cc
	)

set(INCLUDE_FILES
	main_window.hh
	log_window.hh
	control_tab.hh
	qt_log.hh
	)

add_sources()
