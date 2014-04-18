#ifndef ROBOSOCCER_COMMON_GEOMETRY_ANGLETEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_ANGLETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class AngleTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(AngleTest);
		CPPUNIT_TEST(constructor_empty_valueIs0);
		CPPUNIT_TEST(constructor_2_valueIs2);
		CPPUNIT_TEST(constructor_minus2_valueIsMinus2);
		CPPUNIT_TEST(constructor_10_valueIsMinus256);
		CPPUNIT_TEST(constructor_from0And0To1And0And0And1_valueIsPiHalf);
		CPPUNIT_TEST(constructor_from1And1To2And0And0And1_valueIs3PiQuarters);
		CPPUNIT_TEST(constructor_threePointsAndOneTargetEqualToSource_0);
		CPPUNIT_TEST(constructor_targetsEqual_0);
		CPPUNIT_TEST(constructor_startAt1And3EndAtMinus2And1_correctResult);
		CPPUNIT_TEST(getValueBetweenZeroAndTwoPi_negativeValue_correctPositiveValue);
		CPPUNIT_TEST(getHalfRotation_empty_valueIsPi);
		CPPUNIT_TEST(getQuarterRotation_empty_valueIsPiHalf);
		CPPUNIT_TEST(getFullRotation_empty_valueIs0);
		CPPUNIT_TEST(operatorPlus_3And5_valueIsCorrect);
		CPPUNIT_TEST(operatorMinus_Minus3And4_valueIsCorrect);
		CPPUNIT_TEST(operatorMultiply_2And3_valueIsCorrect);
		CPPUNIT_TEST(operatorDivide_3And2_valueIsCorrect);
		CPPUNIT_TEST(operatorMinus_twoAnglesConstructedFromPoints_valueIsNegative);
		CPPUNIT_TEST(abs_1_valueIs1);
		CPPUNIT_TEST(abs_minus1_valueIs1);
		CPPUNIT_TEST(getEighthRotation_empty_valueIsPiQuarter);
		CPPUNIT_TEST(getThreeQuarterRotation_empty_valueIsThreeHalfPi);
		CPPUNIT_TEST(isObtuse_0_false);
		CPPUNIT_TEST(isObtuse_pi_true);
		CPPUNIT_TEST(isObtuse_piQuarter_false);
		CPPUNIT_TEST(isObtuse_minusPiQuarter_false);
		CPPUNIT_TEST(isObtuse_piThreeQuarter_true);
		CPPUNIT_TEST(isObtuse_minusPiThreeQuarter_true);
		CPPUNIT_TEST(getHalfRotation_multiplyWith4per5_valueIs4Piper5);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_valueIs0();
		void constructor_2_valueIs2();
		void constructor_minus2_valueIsMinus2();
		void constructor_10_valueIsMinus256();
		void constructor_from0And0To1And0And0And1_valueIsPiHalf();
		void constructor_from1And1To2And0And0And1_valueIs3PiQuarters();
		void constructor_threePointsAndOneTargetEqualToSource_0();
		void constructor_targetsEqual_0();
		void constructor_startAt1And3EndAtMinus2And1_correctResult();
		void getValueBetweenZeroAndTwoPi_negativeValue_correctPositiveValue();
		void getHalfRotation_empty_valueIsPi();
		void getQuarterRotation_empty_valueIsPiHalf();
		void getFullRotation_empty_valueIs0();
		void operatorPlus_3And5_valueIsCorrect();
		void operatorMinus_Minus3And4_valueIsCorrect();
		void operatorMultiply_2And3_valueIsCorrect();
		void operatorDivide_3And2_valueIsCorrect();
		void operatorMinus_twoAnglesConstructedFromPoints_valueIsNegative();
		void abs_1_valueIs1();
		void abs_minus1_valueIs1();
		void getEighthRotation_empty_valueIsPiQuarter();
		void getThreeQuarterRotation_empty_valueIsThreeHalfPi();
		void isObtuse_0_false();
		void isObtuse_pi_true();
		void isObtuse_piQuarter_false();
		void isObtuse_minusPiQuarter_false();
		void isObtuse_piThreeQuarter_true();
		void isObtuse_minusPiThreeQuarter_true();
		void getHalfRotation_multiplyWith4per5_valueIs4Piper5();
	};
}
}
}

#endif
