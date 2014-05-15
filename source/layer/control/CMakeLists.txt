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
	penaltyoffensive.cpp
	penaltydefensive.cpp
	userinputfetcherimpl.cpp
	userinputfetchermock.cpp
	treenode.cpp
	treenodedecider.cpp
	treenoderesult.cpp
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
	penaltyoffensivetest.cpp
	penaltydefensivetest.cpp
)

add_library(layercontrol ${COMMON_LAYER_CONTROL_SRC})
add_library(layercontroltest ${COMMON_LAYER_CONTROL_TEST_SRC})
