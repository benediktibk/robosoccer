#include "common/logging/loggertest.h"
#include "common/logging/loggerimpl.h"

using namespace RoboSoccer::Common::Logging;


void LoggerTest::write_someText_someText()
{
	LoggerImpl logger;

	logger.enableConsoleOutput();
	logger.enableLogWriting();

	logger.logToGlobalLogFile("some Text");
	logger.logToLogFileOfType(Logger::LogFileTypeField, "some other test.");

	CPPUNIT_ASSERT(true);
}


