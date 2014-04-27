set(COMMON_LAYER_CONTROL_SRC
	robosoccerstate.cpp
	pause.cpp
	preparekickoff.cpp
)

set(COMMON_LAYER_CONTROL_TEST_SRC
	robosoccerstatetest.cpp
	pausetest.cpp
	preparekickofftest.cpp
)

add_library(layercontrol ${COMMON_LAYER_CONTROL_SRC})
add_library(layercontroltest ${COMMON_LAYER_CONTROL_TEST_SRC})
