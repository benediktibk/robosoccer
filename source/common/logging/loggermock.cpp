#include "common/logging/loggermock.h"

using namespace RoboSoccer::Common::Logging;
using namespace std;

LoggerMock::LoggerMock()
{ }

void LoggerMock::logToConsoleAndGlobalLogFile(const string &message)
{
	m_lastMessage = message;
}

void LoggerMock::logErrorToConsoleAndWriteToGlobalLogFile(const string &message)
{
	m_lastMessage = message;
}

void LoggerMock::logToGlobalLogFile(const string &message)
{
	m_lastMessage = message;
}

void LoggerMock::logToLogFileOfType(Logger::LogFileType, const string &message)
{
	m_lastMessage = message;
}

void LoggerMock::enableConsoleOutput()
{
}

void LoggerMock::disableConsoleOutput()
{
}

void LoggerMock::enableLogWriting()
{
}

void LoggerMock::disableLogWriting()
{
}

const string LoggerMock::getLastMessage() const
{
	return m_lastMessage;
}

