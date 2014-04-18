set(COMMON_TIME_SRC
	stopwatch.cpp
	watchimpl.cpp
	watchmock.cpp
)

set(COMMON_TIME_TEST_SRC
	stopwatchtest.cpp
	watchtest.cpp
)

add_library(commontime ${COMMON_TIME_SRC})
add_library(commontimetest ${COMMON_TIME_TEST_SRC})
