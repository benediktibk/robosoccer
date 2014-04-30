set(COMMON_LAYER_AUTONOMOUS_SRC
	intelligentball.cpp
	robotimpl.cpp
	robotmock.cpp
	team.cpp
	enemyteam.cpp
	targetpositionfetcher.cpp
	robotstate.cpp
	robotstatereachedtarget.cpp
	robotstatedriveto.cpp
	robotstateturnto.cpp
	robotstatekick.cpp
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
)

add_library(layerautonomous ${COMMON_LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${COMMON_LAYER_AUTONOMOUS_TEST_SRC})