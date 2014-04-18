set(COMMON_ROUTING_SRC
	route.cpp
	routelengthcompare.cpp
	routerimpl.cpp
	routingobstacle.cpp
	routingresult.cpp
	routermock.cpp
	fieldpositioncheckermock.cpp
)

set(COMMON_ROUTING_TEST_SRC
	routelengthcomparetest.cpp
	routertest.cpp
	routetest.cpp
	routingobstacletest.cpp
	routingresulttest.cpp
)

add_library(commonrouting ${COMMON_ROUTING_SRC})
add_library(commonroutingtest ${COMMON_ROUTING_TEST_SRC})
