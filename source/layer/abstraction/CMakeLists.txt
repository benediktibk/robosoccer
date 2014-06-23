set(COMMON_LAYER_ABSTRACTION_SRC
	controllablerobotimpl.cpp
	controllablerobotmock.cpp
	readablerobot.cpp
	readablerobotimpl.cpp
	readablerobotmock.cpp
	ballimpl.cpp
	ballmock.cpp
	refereeimpl.cpp
	refereemock.cpp
	storageimpl.cpp
	storagemock.cpp
	fieldside.cpp
	robotdrivecontrol.cpp
	fieldpositioncheckerfieldplayer.cpp
	fieldpositioncheckergoalkeeper.cpp
	fieldpositionchecker.cpp
	fieldpositioncheckermock.cpp
	teamcolor.cpp
	tcpserversocketmock.cpp
	tcpserversocketimpl.cpp
)

set(COMMON_LAYER_ABSTRACTION_TEST_SRC
	robotdrivecontroltest.cpp
	fieldpositioncheckerfieldplayertest.cpp
	fieldpositioncheckergoalkeepertest.cpp
)

set(COMPILE_FLAGS_ROSO "-Wno-overflow -Wno-format")
set_source_files_properties(controllablerobotimpl.cpp PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS_ROSO})
set_source_files_properties(ballimpl.cpp PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS_ROSO})
set_source_files_properties(readablerobotimpl.cpp PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS_ROSO})
set_source_files_properties(refereeimpl.cpp PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS_ROSO})
set_source_files_properties(storageimpl.cpp PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS_ROSO})

add_library(layerabstraction ${COMMON_LAYER_ABSTRACTION_SRC})
add_library(layerabstractiontest ${COMMON_LAYER_ABSTRACTION_TEST_SRC})
