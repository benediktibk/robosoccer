set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_library(CPPUNIT_LIBRARY cppunit)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(LIBRARIES
	commonrouting
	commongeometry
	commonstates
	commonlogging
	commonother
	commontime
	layerabstraction
)

if(Boost_FOUND)
	set(LIBRARIES
		${LIBRARIES}
		${Boost_SYSTEM_LIBRARY}
		${Boost_FILESYSTEM_LIBRARY}
	)
endif()

set(LIBRARIES_TEST
	commonroutingtest
	commongeometrytest
	commonstatestest
	commonloggingtest
	commonothertest
	commontimetest
	cppunit
)

add_executable(robosoccer main.cpp)
add_executable(testrunner testregistration.cpp maintestrunner.cpp)

target_link_libraries(robosoccer ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES})

