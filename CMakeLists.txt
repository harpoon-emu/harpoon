cmake_minimum_required(VERSION 3.9)

set(Harpoon_MAJOR_VERSION 0)
set(Harpoon_MINOR_VERSION 1)
set(Harpoon_PATCH_VERSION 0)
set(Harpoon_VERSION
  ${Harpoon_MAJOR_VERSION}.${Harpoon_MINOR_VERSION}.${Harpoon_PATCH_VERSION})

project(Harpoon LANGUAGES CXX VERSION ${Harpoon_VERSION})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(harpoon SHARED
	src/execution/up_execution_unit.cc
	src/execution/exception/invalid_instruction.cc
	src/execution/exception/execution_exception.cc
	src/execution/basic_register.cc
	src/execution/execution_unit.cc
	src/execution/processing_unit.cc
	src/memory/chunked_read_only_memory.cc
	src/memory/exception/write_access_violation.cc
	src/memory/exception/access_violation.cc
	src/memory/exception/memory_exception.cc
	src/memory/exception/read_access_violation.cc
	src/memory/exception/multiplexer_error.cc
	src/memory/random_access_memory.cc
	src/memory/linear_memory.cc
	src/memory/multiplexed_memory.cc
	src/memory/chunked_memory.cc
	src/memory/deserializer/binary_file.cc
	src/memory/deserializer/exception/bad_block_range.cc
	src/memory/deserializer/exception/io.cc
	src/memory/deserializer/deserializer.cc
	src/memory/read_only_memory.cc
	src/memory/linear_read_only_memory.cc
	src/memory/serializer/binary_file.cc
	src/memory/serializer/exception/bad_block_range.cc
	src/memory/serializer/serializer.cc
	src/memory/memory.cc
	src/memory/linear_random_access_memory.cc
	src/memory/main_memory.cc
	src/memory/chunked_random_access_memory.cc
	src/log/log.cc
	src/log/message.cc
	src/log/console_log.cc
	src/exception/hardware_component_exception.cc
	src/exception/harpoon_exception.cc
	src/clock/threaded_clock.cc
	src/clock/clock.cc
	src/hardware_component.cc
	src/computer_system.cc
)

set_target_properties(harpoon PROPERTIES VERSION ${Harpoon_VERSION})
set_target_properties(harpoon PROPERTIES SOVERSION ${Harpoon_MAJOR_VERSION})
set_target_properties(harpoon PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_features(harpoon
	PUBLIC
		cxx_constexpr
		cxx_auto_type
		cxx_variadic_templates
	PRIVATE
		cxx_lambdas
		cxx_range_for
)

target_include_directories(harpoon
	PUBLIC
		$<BUILD_INTERFACE:${Harpoon_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS harpoon EXPORT HarpoonTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT HarpoonTargets
	NAMESPACE Harpoon::
	FILE HarpoonTargets.cmake
	DESTINATION ${CMAKE_INSTALL_DATADIR}/Harpoon/cmake
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/HarpoonConfigVersion.cmake
	VERSION ${Harpoon_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES 
			${CMAKE_CURRENT_BINARY_DIR}/HarpoonConfigVersion.cmake
			HarpoonConfig.cmake
		DESTINATION ${CMAKE_INSTALL_DATADIR}/Harpoon/cmake
)

export(TARGETS harpoon NAMESPACE Harpoon:: FILE HarpoonConfig.cmake)
