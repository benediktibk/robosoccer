#include "common/logging/loggerimpl.h"
#include "common/time/watchimpl.h"
#include <iostream>
#include <ctime>
#include <assert.h>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;

LoggerImpl::LoggerImpl() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(true),
	m_watch(new WatchImpl())
{
	m_logFiles.reserve(7);

	string folder = "log";

	for (int i = 0; i <= 999; ++i)
	{
		stringstream currentStringStream;
		currentStringStream << folder << setw(3) << setfill('0') << i ;

		if(mkdir(currentStringStream.str().c_str(), S_IRWXU|S_IRGRP|S_IXGRP) == 0)
		{
			folder = currentStringStream.str();
			break;
		}

	}

	for (int i = LogFileTypeGlobal; i < LogFileTypeInvalid; ++i)
	{
		string filename = folder;
		filename.append("/");
		filename.append(getNameForLogFileType(static_cast<LogFileType>(i)));

		m_logFiles.push_back(new fstream());
		m_logFiles.back()->open(filename.c_str(), ios_base::out | ios_base::trunc);
	}

	initLogFiles();
}

LoggerImpl::~LoggerImpl()
{
	closeLogFiles();

	while(m_logFiles.size() > 0)
	{
		m_logFiles.back()->close();
		delete m_logFiles.back();
		m_logFiles.pop_back();
	}

	delete m_watch;
	m_watch = 0;
}

void LoggerImpl::logToConsoleAndGlobalLogFile(const string &message)
{
	if (m_consoleOutputEnabled)
		cout << message << endl;
	logToGlobalLogFile(message);
}

void LoggerImpl::logErrorToConsoleAndWriteToGlobalLogFile(const string &message)
{
	if (m_consoleOutputEnabled)
		cerr << message << endl;
	logToGlobalLogFile(message);
}

void LoggerImpl::logToGlobalLogFile(const string &message)
{
	logToLogFileOfType(LogFileTypeGlobal, message);
}

void LoggerImpl::logToLogFileOfType(LogFileType logType, const string &message)
{
	if (!m_logWritingEnabled)
		return;

	if (logType == LogFileTypeInvalid)
		assert(false);

	int choice = static_cast<int>(logType);

	*m_logFiles[choice] << getTimeRelative() << " " << message << endl;
}

void LoggerImpl::enableConsoleOutput()
{
	m_consoleOutputEnabled = true;
}

void LoggerImpl::disableConsoleOutput()
{
	m_consoleOutputEnabled = false;
}

void LoggerImpl::enableLogWriting()
{
	m_logWritingEnabled = true;
}

void LoggerImpl::disableLogWriting()
{
	m_logWritingEnabled = false;
}

void LoggerImpl::initLogFiles()
{
	string message;
	message += "## Starting Log: ";
	message += getTimeAbsolute();
	message += "\n## STARTING ROBOSOCCER\n##\n";

	for (int i = LogFileTypeGlobal; i < LogFileTypeInvalid; i++)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		logToLogFileOfType(currentLogFile, message);
	}
}

void LoggerImpl::closeLogFiles()
{
	string message;
	message += "\n## \n";
	message += "## QUITTING ROBOSOCCER\n## Closing Log: ";
	message += getTimeAbsolute();

	for (int i = LogFileTypeGlobal; i < LogFileTypeInvalid; ++i)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		logToLogFileOfType(currentLogFile, message);
	}
}

string LoggerImpl::getNameForLogFileType(LogFileType logType) const
{
	vector<string> names;
	names.reserve(LogFileTypeInvalid);
	unsigned int choice = static_cast<unsigned int>(logType);

	names.push_back("0_global.txt");
	names.push_back("1_referee.txt");
	names.push_back("2_stateChanges.txt");
	names.push_back("3_robot.txt");
	names.push_back("4_robot1Positions.txt");
	names.push_back("4_robot2Positions.txt");
	names.push_back("4_robotGPositions.txt");

	return names[choice];
}

string LoggerImpl::getTimeAbsolute() const
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	return string(buffer);
}

string LoggerImpl::getTimeRelative() const
{
	stringstream stream;
	stream << m_watch->getTime();
	return stream.str();
}
