#ifndef ROBOSOCCER_COMMON_OTHER_RANDOMDECISIONTEST_H
#define ROBOSOCCER_COMMON_OTHER_RANDOMDECISIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
class RandomDecisionTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(RandomDecisionTest);
	 CPPUNIT_TEST(decide_possibility0_false);
	 CPPUNIT_TEST(decide_possibility1_true);
	 CPPUNIT_TEST(decide_called1000TimesAndPossibilityAHalf_around500TimesTrue);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void decide_possibility0_false();
	 void decide_possibility1_true();
	 void decide_called1000TimesAndPossibilityAHalf_around500TimesTrue();
};
}
}
}

#endif
