set(COMMON_LAYER_ABSTRACTION_SRC
	controllablerobotimpl.cpp
	readablerobotimpl.cpp
	controllablerobotmock.cpp
	readablerobotmock.cpp
)

add_library(layerabstraction ${COMMON_LAYER_ABSTRACTION_SRC})