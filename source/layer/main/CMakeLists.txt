set(COMMON_LAYER_MAIN_SRC
	inputargumentparser.cpp
	application.cpp
)

set(COMMON_LAYER_MAIN_TEST_SRC
	inputargumentparsertest.cpp
	applicationtest.cpp
)

add_library(layermain ${COMMON_LAYER_MAIN_SRC})
add_library(layermaintest ${COMMON_LAYER_MAIN_TEST_SRC})
