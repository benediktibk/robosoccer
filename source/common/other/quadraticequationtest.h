#ifndef ROBOSOCCER_COMMON_OTHER_QUADRATICEQUATIONTEST_H
#define ROBOSOCCER_COMMON_OTHER_QUADRATICEQUATIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
	class QuadraticEquationTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(QuadraticEquationTest);
		CPPUNIT_TEST(getSolutions_noRealSolution_resultSizeIs0);
		CPPUNIT_TEST(getSolutions_oneRealSolution_solutionIsCorrect);
		CPPUNIT_TEST(getSolutions_twoRealSolutions_solutionsAreCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getSolutions_noRealSolution_resultSizeIs0();
		void getSolutions_oneRealSolution_solutionIsCorrect();
		void getSolutions_twoRealSolutions_solutionsAreCorrect();
	};
}
}
}

#endif


