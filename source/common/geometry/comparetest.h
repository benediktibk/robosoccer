#ifndef ROBOSOCCER_COMMON_GEOMETRY_COMPARETEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_COMPARETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class CompareTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CompareTest);
		CPPUNIT_TEST(isFuzzyEqual_twoNearlyEqualVectorsWithExtraAgnleCompare_true);
		CPPUNIT_TEST(isFuzzyEqual_twoNearlyEqualVectorsWithExtraAgnleCompareAndAngleCompareToSmall_false);
		CPPUNIT_TEST(isFuzzyEqual_twoCompletelyEqualVectors_true);
		CPPUNIT_TEST(isFuzzyEqual_twoNearlyEqualVectors_true);
		CPPUNIT_TEST(isFuzzyEqual_twoVectorsWithDifferentSize_false);
		CPPUNIT_TEST(isFuzzyEqual_towVectorsWithOrientedPositions_true);
		CPPUNIT_TEST(isFuzzyEqual_twoDifferentVectorsWithOrientedPositions_false);
		CPPUNIT_TEST(isFuzzyEqual_towVectorsWithOrientedPositionsInDiffrentOrder_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesNearPi_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesNearZero_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesWhichAreNotEqual_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesWhichHave90DegreesDifference_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesWhichHave270DegreesDifference_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAngelsNear90Degrees_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAngelsNear270Degrees_true);
		CPPUNIT_TEST(isFuzzyEqual_twoEqualCircles_true);
		CPPUNIT_TEST(isFuzzyEqual_twoCirclesWithDifferentCenter_false);
		CPPUNIT_TEST(isFuzzyEqual_twoCirclesWithDifferentDiameter_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isFuzzyEqual_twoNearlyEqualVectorsWithExtraAgnleCompare_true();
		void isFuzzyEqual_twoNearlyEqualVectorsWithExtraAgnleCompareAndAngleCompareToSmall_false();
		void isFuzzyEqual_twoCompletelyEqualVectors_true();
		void isFuzzyEqual_twoNearlyEqualVectors_true();
		void isFuzzyEqual_twoVectorsWithDifferentSize_false();
		void isFuzzyEqual_towVectorsWithOrientedPositions_true();
		void isFuzzyEqual_twoDifferentVectorsWithOrientedPositions_false();
		void isFuzzyEqual_towVectorsWithOrientedPositionsInDiffrentOrder_false();
		void isFuzzyEqual_twoAnglesNearPi_true();
		void isFuzzyEqual_twoAnglesNearZero_true();
		void isFuzzyEqual_twoAnglesWhichAreNotEqual_false();
		void isFuzzyEqual_twoAnglesWhichHave90DegreesDifference_false();
		void isFuzzyEqual_twoAnglesWhichHave270DegreesDifference_false();
		void isFuzzyEqual_twoAngelsNear90Degrees_true();
		void isFuzzyEqual_twoAngelsNear270Degrees_true();
		void isFuzzyEqual_twoEqualCircles_true();
		void isFuzzyEqual_twoCirclesWithDifferentCenter_false();
		void isFuzzyEqual_twoCirclesWithDifferentDiameter_false();
	};
}
}
}

#endif
