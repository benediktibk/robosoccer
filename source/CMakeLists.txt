cmake_minimum_required(VERSION 2.8)
project(robosoccer)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_CXX_FLAGS_COMMON "-Wall -Wextra -Werror -ansi -fPIE -Wswitch-enum")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_COMMON} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_COMMON} -g")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COMMON} -g -fprofile-arcs -ftest-coverage")

include_directories(
	.
	external/cppunit/include
)

if(NOT USE_SIM_LIBRARIES)
	include_directories(
		external/roso/include/roboctrl
		external/roso/include/rtdb
		external/roso/include/rosomath
	)
	message("using the normal libraries")
else()
	include_directories(
		external/roso/include-sim/roboctrl
		external/roso/include-sim/rtdb
		external/roso/include-sim/rosomath
	)
	message("using the simulation libraries")
endif()

add_custom_target(
	checkIncludeGuards ALL
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/checkIncludeGuards.sh
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
	testcoverage
	${CMAKE_CURRENT_SOURCE_DIR}/testCoverage.sh ${CMAKE_CURRENT_SOURCE_DIR}
	DEPENDS testrunner
)

find_package(Doxygen)
if(DOXYGEN_FOUND)

file(COPY
	${CMAKE_CURRENT_SOURCE_DIR}/../README.md
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)


execute_process(COMMAND git rev-list --count HEAD
				OUTPUT_VARIABLE GIT_CURRENT_REV)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_target(

	doc

	rm -f ${CMAKE_CURRENT_BINARY_DIR}/documentation/html/formula.repository && ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 2>&1 | grep -v "stl_vector.h" | grep -v "parameter '__"

	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

	COMMENT "Generating API documentation with Doxygen" VERBATIM

	DEPENDS ${COMMON_SRC} ${COMMON_TEST_SRC}

)
endif(DOXYGEN_FOUND)

add_subdirectory(common)
add_subdirectory(layer)
add_subdirectory(main)
