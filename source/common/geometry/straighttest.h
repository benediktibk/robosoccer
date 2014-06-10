#ifndef ROBOSOCCER_COMMON_GEOMETRY_STRAIGHTTEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_STRAIGHTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
class StraightTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(StraightTest);
		CPPUNIT_TEST(isTargetPointRightOfLine_straightIsXAxisAndPointIsRight_true);
		CPPUNIT_TEST(isTargetPointRightOfLine_straightIsYAxisAndPointIsLeft_false);
		CPPUNIT_TEST(isTargetPointRightOfLine_straightAndPointIsRight_true);
		CPPUNIT_TEST(isTargetPointRightOfLine_straightIsNegativeXAxisAndPointIsRightOfXAxis_false);
		CPPUNIT_TEST(isTargetPointRightOfLine_straightThroughOriginPointIsRight_true);
		CPPUNIT_TEST(getIntersectPoint_linesAreParralel_noIntersect);
		CPPUNIT_TEST(getIntersectPoint_linesAreIntersecting_oneIntersect);
		CPPUNIT_TEST(getIntersectPoint_linesAreEqual_noIntersect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isTargetPointRightOfLine_straightIsXAxisAndPointIsRight_true();
		void isTargetPointRightOfLine_straightIsYAxisAndPointIsLeft_false();
		void isTargetPointRightOfLine_straightAndPointIsRight_true();
		void isTargetPointRightOfLine_straightIsNegativeXAxisAndPointIsRightOfXAxis_false();
		void isTargetPointRightOfLine_straightThroughOriginPointIsRight_true();
		void getIntersectPoint_linesAreParralel_noIntersect();
		void getIntersectPoint_linesAreIntersecting_oneIntersect();
		void getIntersectPoint_linesAreEqual_noIntersect();
	};
}
}
}

#endif
