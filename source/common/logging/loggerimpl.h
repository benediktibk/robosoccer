#ifndef ROBOSOCCER_COMMON_LOGGING_LOGGERIMPL_H
#define ROBOSOCCER_COMMON_LOGGING_LOGGERIMPL_H

#include <vector>
#include "common/logging/logger.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
}
namespace Logging
{
class LoggerImpl :
		public Logger
	{

	public:
		LoggerImpl();
		virtual ~LoggerImpl();

		virtual void logToConsoleAndGlobalLogFile(const std::string &message);
		virtual void logErrorToConsoleAndWriteToGlobalLogFile(const std::string &message);
		virtual void logToGlobalLogFile(const std::string &message);
		virtual void logToLogFileOfType(LogFileType logType, const std::string &message);

		virtual void enableConsoleOutput();
		virtual void disableConsoleOutput();
		virtual void enableLogWriting();
		virtual void disableLogWriting();

	private:
		std::string getNameForLogFileType(LogFileType logType) const;
		void initLogFiles();
		void closeLogFiles();
		std::string getTimeAbsolute() const;
		std::string getTimeRelative() const;

	private:
		bool m_consoleOutputEnabled;
		bool m_logWritingEnabled;
		Time::Watch *m_watch;

		std::vector<std::fstream*> m_logFiles;

	};
}
}
}

#endif


