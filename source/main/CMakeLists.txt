set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CPPUNIT_LIBRARY
	${CMAKE_SOURCE_DIR}/external/cppunit/src/cppunit/.libs/libcppunit.a
)

set(BOOST_LIBRARIES
	${CMAKE_SOURCE_DIR}/external/boost/build/lib/libboost_filesystem.a
	${CMAKE_SOURCE_DIR}/external/boost/build/lib/libboost_system.a
)

set(LIBRARIES
	layermain
	layerabstraction
	commonrouting
	commongeometry
	commonstates
	commonlogging
	commonother
	commontime
	${BOOST_LIBRARIES}
)

set(LIBRARIES_TEST
	layermaintest
	commonroutingtest
	commongeometrytest
	commonstatestest
	commonloggingtest
	commonothertest
	commontimetest
	${CPPUNIT_LIBRARY}
)

add_executable(robosoccer main.cpp)
add_executable(abstractiontest mainabstractiontest.cpp)
add_executable(testrunner testregistration.cpp maintestrunner.cpp)

target_link_libraries(robosoccer ${LIBRARIES})
target_link_libraries(abstractiontest ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES})

