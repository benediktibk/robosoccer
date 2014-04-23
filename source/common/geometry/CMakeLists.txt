set(COMMON_GEOMETRY_SRC
	angle.cpp
	circle.cpp
	line.cpp
	path.cpp
	pathintersectpoints.cpp
	point.cpp
	pointdistancecompare.cpp
	rectangle.cpp
	compare.cpp
	orientedposition.cpp
    rectangleroundedcorners.cpp
)

set(COMMON_GEOMETRY_TEST_SRC
	angletest.cpp
	circletest.cpp
	linetest.cpp
	pathtest.cpp
	pathintersectpointstest.cpp
	pointtest.cpp
	pointdistancecomparetest.cpp
	rectangletest.cpp
	comparetest.cpp
	orientedpositiontest.cpp
    rectangleroundedcornerstest.cpp
)

add_library(commongeometry ${COMMON_GEOMETRY_SRC})
add_library(commongeometrytest ${COMMON_GEOMETRY_TEST_SRC})
