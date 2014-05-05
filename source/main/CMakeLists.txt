set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CPPUNIT_LIBRARY
	${CMAKE_SOURCE_DIR}/external/cppunit/src/cppunit/.libs/libcppunit.a
)

set(ROSO_LIBRARIES
	${CMAKE_SOURCE_DIR}/external/roso/lib/libpololu_rtdb.so
	${CMAKE_SOURCE_DIR}/external/roso/lib/librosomath.a
	${CMAKE_SOURCE_DIR}/external/roso/lib/libkogmo_rtdb.so
)

set(LIBRARIES
	layermain
	layercontrol
	layerautonomous
	layerabstraction
	commonrouting
	commongeometry
	commonstates
	commonlogging
	commonother
	commontime
	${ROSO_LIBRARIES}
)

set(LIBRARIES_TEST
	layermaintest
	layercontroltest
	layerautonomoustest
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
add_executable(autonomoustest mainautonomoustest.cpp)
add_executable(testrunner testregistration.cpp maintestrunner.cpp)

target_link_libraries(robosoccer ${LIBRARIES})
target_link_libraries(abstractiontest ${LIBRARIES})
target_link_libraries(autonomoustest ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES})

