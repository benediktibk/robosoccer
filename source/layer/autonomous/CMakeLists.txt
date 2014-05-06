set(COMMON_LAYER_AUTONOMOUS_SRC
	robotimpl.cpp
	robotmock.cpp
	teamimpl.cpp
	teammock.cpp
	enemyteamimpl.cpp
	enemyteammock.cpp
	targetpositionfetcher.cpp
	robotstate.cpp
	robotstatereachedtarget.cpp
	robotstatedriveto.cpp
	robotstateturnto.cpp
	robotstatekick.cpp
	intelligentballimpl.cpp
	intelligentballmock.cpp
	obstaclefetcher.cpp
)

set(COMMON_LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
	teamtest.cpp
	enemyteamtest.cpp
	targetpositionfetchertest.cpp
	robotstatetest.cpp
	robotstatereachedtargettest.cpp
	robotstatedrivetotest.cpp
	robotstateturntotest.cpp
	robotstatekicktest.cpp
	intelligentballtest.cpp
	obstaclefetchertest.cpp
)

add_library(layerautonomous ${COMMON_LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${COMMON_LAYER_AUTONOMOUS_TEST_SRC})
