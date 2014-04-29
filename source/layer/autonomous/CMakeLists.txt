set(COMMON_LAYER_AUTONOMOUS_SRC
	intelligentball.cpp
	robotimpl.cpp
	robotmock.cpp
	team.cpp
	enemyteam.cpp
	targetpositionfetcher.cpp
)

set(COMMON_LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
	teamtest.cpp
	enemyteamtest.cpp
	targetpositionfetchertest.cpp
)

add_library(layerautonomous ${COMMON_LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${COMMON_LAYER_AUTONOMOUS_TEST_SRC})
