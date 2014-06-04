set(COMMON_LAYER_AUTONOMOUS_SRC
	robotimpl.cpp
	robotmock.cpp
	teamimpl.cpp
	teammock.cpp
	enemyteamimpl.cpp
	enemyteammock.cpp
	targetpositionfetcher.cpp
	intelligentballimpl.cpp
	intelligentballmock.cpp
	obstaclefetcherimpl.cpp
	obstaclefetchermock.cpp
	obstaclesourcemock.cpp
)

set(COMMON_LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
	teamtest.cpp
	enemyteamtest.cpp
	targetpositionfetchertest.cpp
	intelligentballtest.cpp
	obstaclefetchertest.cpp
)

set(COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_SRC
	robotstates/robotstate.cpp
	robotstates/robotstatereachedtarget.cpp
	robotstates/robotstatedriveto.cpp
	robotstates/robotstatedrivetodirect.cpp
	robotstates/robotstatedrivetodirectdriving.cpp
	robotstates/robotstatedrivetodirectinitialrotation.cpp
	robotstates/robotstatedrivetodirectfinalrotation.cpp
	robotstates/robotstateturnto.cpp
	robotstates/robotstatekick.cpp
)

set(COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_TEST_SRC
	robotstates/robotstatetest.cpp
	robotstates/robotstatereachedtargettest.cpp
	robotstates/robotstatedrivetotest.cpp
	robotstates/robotstatedrivetodirecttest.cpp
	robotstates/robotstatedrivetodirectdrivingtest.cpp
	robotstates/robotstatedrivetodirectinitialrotationtest.cpp
	robotstates/robotstatedrivetodirectfinalrotationtest.cpp
	robotstates/robotstateturntotest.cpp
	robotstates/robotstatekicktest.cpp
)

add_library(layerautonomous ${COMMON_LAYER_AUTONOMOUS_SRC} ${COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_SRC})
add_library(layerautonomoustest ${COMMON_LAYER_AUTONOMOUS_TEST_SRC} ${COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_TEST_SRC})
