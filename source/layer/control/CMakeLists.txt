set(COMMON_LAYER_CONTROL_SRC
	robosoccerstate.cpp
	pause.cpp
	preparekickoff.cpp
	play.cpp
	preparepenalty.cpp
	preparekickoffoffensive.cpp
	preparekickoffdefensive.cpp
	kickoffoffensive.cpp
	kickoffdefensive.cpp
	preparepenaltyoffensive.cpp
	preparepenaltydefensive.cpp
)

set(COMMON_LAYER_CONTROL_TEST_SRC
	robosoccerstatetest.cpp
	pausetest.cpp
	preparekickofftest.cpp
	playtest.cpp
	preparepenaltytest.cpp
	preparekickoffoffensivetest.cpp
	preparekickoffdefensivetest.cpp
	kickoffoffensivetest.cpp
	kickoffdefensivetest.cpp
	preparepenaltyoffensivetest.cpp
	preparepenaltydefensivetest.cpp
)

add_library(layercontrol ${COMMON_LAYER_CONTROL_SRC})
add_library(layercontroltest ${COMMON_LAYER_CONTROL_TEST_SRC})
