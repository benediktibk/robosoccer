#include "common/logging/loggerimpl.h"
#include <iostream>
#include <ctime>
#include <assert.h>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>

using namespace std;
using namespace RoboSoccer::Common::Logging;

LoggerImpl::LoggerImpl() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(true)
{
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

	string globalLogFile = folder;
	globalLogFile.append("/0_global.txt");

	string refereeLogFile = folder;
	refereeLogFile.append("/1_referee.txt");

	string stateChangesLogFile = folder;
	stateChangesLogFile.append("/2_stateChanges.txt");

	string robotLogFile = folder;
	robotLogFile.append("/3_robot.txt");

	m_globalLogFile.open(globalLogFile.c_str(), ios_base::out | ios_base::trunc);
	m_refereeLogFile.open(refereeLogFile.c_str(), ios_base::out | ios_base::trunc);
	m_stateChangesLogFile.open(stateChangesLogFile.c_str(), ios_base::out | ios_base::trunc);
	m_robotLogFile.open(robotLogFile.c_str(), ios_base::out | ios_base::trunc);

	initLogFiles();
}

LoggerImpl::~LoggerImpl()
{
	closeLogFiles();

	m_globalLogFile.close();
	m_refereeLogFile.close();
	m_stateChangesLogFile.close();
	m_robotLogFile.close();
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
	if (m_logWritingEnabled)
		m_globalLogFile << message << endl;
}

void LoggerImpl::logToLogFileOfType(LogFileType logType, const string &message)
{
	if (!m_logWritingEnabled)
		return;

	switch (logType)
	{
	case LogFileTypeGlobal:
		m_globalLogFile << message << endl;
		break;

	case LogFileTypeReferee:
		m_refereeLogFile << message << endl;
		break;

	case LogFileTypeStateChanges:
		m_stateChangesLogFile << message << endl;
		break;

	case LogFileTypeRobot:
		m_robotLogFile << message << endl;
		break;

	case LogFileTypeInvalid:
		assert(false);
		break;
	}
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
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	string timestring(buffer);

	string message;
	message += "## Starting Log: ";
	message += timestring;
	message += "\n## STARTING ROBOSOCCER\n##\n";

	for (int i = LogFileTypeGlobal; i < LogFileTypeInvalid; i++)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		logToLogFileOfType(currentLogFile, message);
	}
}

void LoggerImpl::closeLogFiles()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	string timestring(buffer);

	string message;
	message += "\n## \n";
	message += "## QUITTING ROBOSOCCER\n## Closing Log: ";
	message += timestring;

	for (int i = LogFileTypeGlobal; i < LogFileTypeInvalid; ++i)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		logToLogFileOfType(currentLogFile, message);
	}
}

