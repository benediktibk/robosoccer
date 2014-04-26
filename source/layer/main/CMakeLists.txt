set(COMMON_LAYER_MAIN_SRC
	application.cpp
	fieldpositioncheckerfieldplayer.cpp
	fieldpositioncheckergoalkeeper.cpp
	targetpositionfetcher.cpp
	intelligentball.cpp
)

set(COMMON_LAYER_MAIN_TEST_SRC
	applicationtest.cpp
	fieldpositioncheckerfieldplayertest.cpp
	fieldpositioncheckergoalkeepertest.cpp
	targetpositionfetchertest.cpp
)

add_library(layermain ${COMMON_LAYER_MAIN_SRC})
add_library(layermaintest ${COMMON_LAYER_MAIN_TEST_SRC})
