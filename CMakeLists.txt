cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

include(functions)

project(harpoon)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_COMMON_CXX_FLAGS
		-std=c++14
		-Werror
		-Weverything
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-padded
		-Wno-redundant-parens
		-Wno-extra-semi-stmt
		-Wno-unknown-warning-option
		)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(CMAKE_COMMON_CXX_FLAGS
		-std=c++14
		-Wall
		-Werror
		)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_COMMON_CXX_FLAGS
		/W4
		/WX
		/w44265
		/bigobj
		)
endif()

string(REGEX REPLACE ";" " " CMAKE_COMMON_CXX_FLAGS "${CMAKE_COMMON_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_COMMON_CXX_FLAGS}")

set(CURRENT_TARGET_DIR "${PROJECT_SOURCE_DIR}")
set(SOURCES CACHE INTERNAL "SOURCES")
set(INCLUDES CACHE INTERNAL "INCLUDES")

add_subdirectory(src)

add_library(harpoon
	${SOURCES}
	${INCLUDES}
	)

include_directories(include)
