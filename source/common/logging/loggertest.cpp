#include "common/logging/loggertest.h"
#include "common/logging/loggerimpl.h"

using namespace RoboSoccer::Common::Logging;


void LoggerTest::write_someText_someText()
{
	LoggerImpl logger;

	logger.enableConsoleOutput();
	logger.enableLogWriting();

	//! deletes the generated files, in order to reduce the amout of log folders
	logger.deleteLogFolderAfterFinish();

	logger.logToGlobalLogFile("some Text");
	logger.logToLogFileOfType(Logger::LogFileTypeReferee, "some other test.");

	CPPUNIT_ASSERT(true);
}

void LoggerTest::write_testAllLogTypes_someText()
{
	LoggerImpl logger;

	logger.enableConsoleOutput();
	logger.enableLogWriting();

	//! deletes the generated files, in order to reduce the amout of log folders
	logger.deleteLogFolderAfterFinish();

	logger.logToLogFileOfType(Logger::LogFileTypeControllableRobotTwo, "some text");

	CPPUNIT_ASSERT(true);
}
