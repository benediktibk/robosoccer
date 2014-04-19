set(COMMON_STATES_SRC
	state.cpp
	statemachine.cpp
	statemock.cpp
)

set(COMMON_STATES_TEST_SRC
	statemachinetest.cpp
	statetest.cpp
)

add_library(commonstates ${COMMON_STATES_SRC})
add_library(commonstatestest ${COMMON_STATES_TEST_SRC})
