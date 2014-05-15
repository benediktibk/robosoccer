set(COMMON_OTHER_SRC
	pidcontroller.cpp
	quadraticequation.cpp
	randomdecision.cpp
	segfaultstacktraceprinter.cpp
	compare.cpp
)

set(COMMON_OTHER_TEST_SRC
	pidcontrollertest.cpp
	quadraticequationtest.cpp
	randomdecisiontest.cpp
	signumtest.cpp
	comparetest.cpp
)

add_library(commonother ${COMMON_OTHER_SRC})
add_library(commonothertest ${COMMON_OTHER_TEST_SRC})
