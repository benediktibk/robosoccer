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
	robotstates/reachedtarget.cpp
	robotstates/driveto.cpp
	robotstates/drivetodirectdriving.cpp
	robotstates/drivetodirectinitialrotation.cpp
	robotstates/drivetodirectfinalrotation.cpp
	robotstates/drivetoinitialrotation.cpp
	robotstates/drivetofinalrotation.cpp
	robotstates/drivetodriving.cpp
	robotstates/drivetoinvalidroute.cpp
	robotstates/turnto.cpp
	robotstates/kick.cpp
	robotstates/drivemode.cpp
)

set(COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_TEST_SRC
	robotstates/robotstatetest.cpp
	robotstates/reachedtargettest.cpp
	robotstates/drivetodirectdrivingtest.cpp
	robotstates/drivetodirectinitialrotationtest.cpp
	robotstates/drivetodirectfinalrotationtest.cpp
	robotstates/drivetoinitialrotationtest.cpp
	robotstates/drivetofinalrotationtest.cpp
	robotstates/drivetodrivingtest.cpp
	robotstates/drivetoinvalidroutetest.cpp
	robotstates/turntotest.cpp
	robotstates/kicktest.cpp
)

add_library(layerautonomous ${COMMON_LAYER_AUTONOMOUS_SRC} ${COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_SRC})
add_library(layerautonomoustest ${COMMON_LAYER_AUTONOMOUS_TEST_SRC} ${COMMON_LAYER_AUTONOMOUS_ROBOTSTATES_TEST_SRC})
