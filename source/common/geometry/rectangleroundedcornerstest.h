#ifndef ROBOSOCCER_COMMON_GEOMETRY_RECTANGLEROUNDEDCORNERSTEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_RECTANGLEROUNDEDCORNERSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
	class Compare;
}
namespace Geometry
{
	class RectangleRoundedCornersTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RectangleRoundedCornersTest);
		CPPUNIT_TEST(isInside_isOutsideRoundedRectButInsideRect_false);
		CPPUNIT_TEST(isInside_isInsideRect_true);
		CPPUNIT_TEST(isInside_isInsideRoundCornerLL_true);
		CPPUNIT_TEST(isInside_isInsideRoundCornerLU_true);
		CPPUNIT_TEST(isInside_isInsideRoundCornerRL_true);
		CPPUNIT_TEST(isInside_isInsideRoundCornerRU_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isInside_isOutsideRoundedRectButInsideRect_false();
		void isInside_isInsideRect_true();
		void isInside_isInsideRoundCornerLL_true();
		void isInside_isInsideRoundCornerLU_true();
		void isInside_isInsideRoundCornerRL_true();
		void isInside_isInsideRoundCornerRU_true();
	};
}
}
}

#endif
