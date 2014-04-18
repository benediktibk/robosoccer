set(COMMON_LOGGING_SRC
	loggerimpl.cpp
	loggermock.cpp
)

set(COMMON_LOGGING_TEST_SRC
	loggertest.cpp
)

add_library(commonlogging ${COMMON_LOGGING_SRC})
add_library(commonloggingtest ${COMMON_LOGGING_TEST_SRC})
