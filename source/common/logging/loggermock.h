#ifndef ROBOSOCCER_COMMON_LOGGING_LOGGERMOCK_H
#define ROBOSOCCER_COMMON_LOGGING_LOGGERMOCK_H

#include "common/logging/logger.h"

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class LoggerMock :
		public Logger
	{
	public:
		LoggerMock();

		virtual void logToConsoleAndGlobalLogFile(const std::string &message);
		virtual void logErrorToConsoleAndWriteToGlobalLogFile(const std::string &message);
		virtual void logToGlobalLogFile(const std::string &message);
		virtual void logToLogFileOfType(LogFileType logType, const std::string &message);

		virtual void enableConsoleOutput();
		virtual void disableConsoleOutput();
		virtual void enableLogWriting();
		virtual void disableLogWriting();

		const std::string getLastMessage() const;

	private:
		std::string m_lastMessage;
	};
}
}
}

#endif


