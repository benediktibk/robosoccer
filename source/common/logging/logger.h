#ifndef ROBOSOCCER_COMMON_LOGGING_LOGGER_H
#define ROBOSOCCER_COMMON_LOGGING_LOGGER_H

#include <string>
#include <fstream>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
class Logger
	{
	public:
		enum LogFileType
		{
			LogFileTypeGlobal,
			LogFileTypeStateChanges,
			LogFileTypeField,
			LogFileTypeFieldDetection,
			LogFileTypeRobot
		};

	public:
		virtual ~Logger() { }
		virtual void logToConsoleAndGlobalLogFile(const std::string &message) = 0;
		virtual void logErrorToConsoleAndWriteToGlobalLogFile(const std::string &message) = 0;
		virtual void logToGlobalLogFile(const std::string &message) = 0;
		virtual void logToLogFileOfType(LogFileType logType, const std::string &message) = 0;

		virtual void enableConsoleOutput() = 0;
		virtual void disableConsoleOutput() = 0;
		virtual void enableLogWriting() = 0;
		virtual void disableLogWriting() = 0;

	};
}
}
}

#endif

