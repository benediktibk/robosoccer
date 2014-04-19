set(COMMON_LAYER_ABSTRACTION_SRC
	controllablerobotimpl.cpp
	controllablerobotmock.cpp
	readablerobotimpl.cpp
	readablerobotmock.cpp
	ballimpl.cpp
	ballmock.cpp
)

add_library(layerabstraction ${COMMON_LAYER_ABSTRACTION_SRC})