#ifndef ROBOSOCCER_COMMON_LOGGING_LOGGERTEST_H
#define ROBOSOCCER_COMMON_LOGGING_LOGGERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
class LoggerTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LoggerTest);
		CPPUNIT_TEST(write_someText_someText);
		CPPUNIT_TEST_SUITE_END();

	private:
		void write_someText_someText();
	};
}
}
}

#endif


