#ifndef ROBOSOCCER_COMMON_GEOMETRY_PATHINTERSECTPOINTSTEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_PATHINTERSECTPOINTSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class PathIntersectPointsTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(PathIntersectPointsTest);
		CPPUNIT_TEST(constructor_createDefaultObject_intersectPointsCountIs2);
		CPPUNIT_TEST(constructor_createDefaultObject_intersectTypeFromLeft);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_createDefaultObject_intersectPointsCountIs2();
		void constructor_createDefaultObject_intersectTypeFromLeft();

	};
}
}
}

#endif


