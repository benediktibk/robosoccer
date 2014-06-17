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
		CPPUNIT_TEST(isFuzzyEqual_twoCompletelyEqualVectors_true);
		CPPUNIT_TEST(isFuzzyEqual_twoNearlyEqualVectors_true);
		CPPUNIT_TEST(isFuzzyEqual_twoVectorsWithDifferentSize_false);
		CPPUNIT_TEST(isFuzzyEqual_twoDifferentVectors_false);
		CPPUNIT_TEST(isFuzzyEqual_towVectorsWithOrientedPositions_true);
		CPPUNIT_TEST(isFuzzyEqual_twoVectorsWithOrientedPositions_false);
		CPPUNIT_TEST(isFuzzyEqual_towVectorsWithOrientedPositionsInDiffrentOrder_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesNearPi_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesNearZero_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesWhichAreNotEqual_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesWhichHave90DegreesDifference_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAnglesWhichHave270DegreesDifference_false);
		CPPUNIT_TEST(isFuzzyEqual_twoAngelsNear90Degrees_true);
		CPPUNIT_TEST(isFuzzyEqual_twoAngelsNear270Degrees_true);
		CPPUNIT_TEST(isFuzzyGreater_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyGreater);
		CPPUNIT_TEST(isFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzySmaller);
		CPPUNIT_TEST(isStrictFuzzyGreater_twoPointOneAndTwoAndEpsilonZeroPointZeroFife_resultIsStrictFuzzyGreater);
		CPPUNIT_TEST(isStrictFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointZeroFife_resultIsStrictFuzzySmaller);
		CPPUNIT_TEST(isStrictFuzzyGreater_onlyLittleBitGreater_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isFuzzyEqual_twoCompletelyEqualVectors_true();
		void isFuzzyEqual_twoNearlyEqualVectors_true();
		void isFuzzyEqual_twoVectorsWithDifferentSize_false();
		void isFuzzyEqual_twoDifferentVectors_false();
		void isFuzzyEqual_towVectorsWithOrientedPositions_true();
		void isFuzzyEqual_twoVectorsWithOrientedPositions_false();
		void isFuzzyEqual_towVectorsWithOrientedPositionsInDiffrentOrder_true();
		void isFuzzyEqual_twoAnglesNearPi_true();
		void isFuzzyEqual_twoAnglesNearZero_true();
		void isFuzzyEqual_twoAnglesWhichAreNotEqual_false();
		void isFuzzyEqual_twoAnglesWhichHave90DegreesDifference_false();
		void isFuzzyEqual_twoAnglesWhichHave270DegreesDifference_false();
		void isFuzzyEqual_twoAngelsNear90Degrees_true();
		void isFuzzyEqual_twoAngelsNear270Degrees_true();
		void isFuzzyGreater_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyGreater();
		void isFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzySmaller();
		void isStrictFuzzyGreater_twoPointOneAndTwoAndEpsilonZeroPointZeroFife_resultIsStrictFuzzyGreater();
		void isStrictFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointZeroFife_resultIsStrictFuzzySmaller();
		void isStrictFuzzyGreater_onlyLittleBitGreater_false();
	};
}
}
}

#endif
