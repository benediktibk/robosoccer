#include "layer/main/inputargumentparser.h"
#include <stdlib.h>
#include <sstream>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

InputArgumentParser::InputArgumentParser(vector<string> const &arguments) :
	m_disableHardwareCheck(false),
	m_disableRouteServer(false),
	m_valid(true),
	m_routeServerPortSet(false),
	m_disableLogging(false)
{
	list<string> argumentsList(arguments.begin() + 1, arguments.end());
	bool teamColorSet = false;
	bool clientNumberSet = false;
	bool disableHardwareCheckSet = false;
	bool disableRouteServerSet = false;
	bool disableLoggingSet = false;

	while (m_valid && !argumentsList.empty())
	{
		string argument = argumentsList.front();
		argumentsList.pop_front();

		if (argument == "--setOwnTeamColor" && !teamColorSet)
		{
			parseTeamColor(argumentsList);
			teamColorSet = true;
		}
		else if (argument == "--setOwnClientNumber" && !clientNumberSet)
		{
			parseClientNumber(argumentsList);
			clientNumberSet = true;
		}
		else if (argument == "--disableHardwareCheck" && !disableHardwareCheckSet)
		{
			parseDisableHardwareCheck();
			disableHardwareCheckSet = true;
		}
		else if (argument == "--disableRouteServer" && !disableRouteServerSet)
		{
			parseDisableRouteServer();
			disableRouteServerSet = true;
		}
		else if (argument == "--routeServerPort" && !m_routeServerPortSet)
		{
			parseRouteServerPort(argumentsList);
			m_routeServerPortSet = true;
		}
		else if (argument == "--disableLogging" && !disableLoggingSet)
		{
			parseDisableLogging();
			disableLoggingSet = true;
		}
		else
			m_valid = false;
	}

	if (!teamColorSet || !clientNumberSet || (m_disableRouteServer && m_routeServerPortSet))
		m_valid = false;
}

bool InputArgumentParser::isValid() const
{
	return m_valid;
}

TeamColor InputArgumentParser::getOwnTeamColor() const
{
	return m_ownTeamColor;
}

int InputArgumentParser::getOwnClientNumber() const
{
	return m_ownClientNumber;
}

bool InputArgumentParser::disableHardwareCheck() const
{
	return m_disableHardwareCheck;
}

unsigned int InputArgumentParser::getRouteServePort() const
{
	return m_routeServerPort;
}

bool InputArgumentParser::routeServerPortSet() const
{
	return m_routeServerPortSet;
}

bool InputArgumentParser::disableRouteServer() const
{
	return m_disableRouteServer;
}

bool InputArgumentParser::disableLogging() const
{
	return m_disableLogging;
}

string InputArgumentParser::usage() const
{
	stringstream stream;

	stream << "usage: " << endl;
	stream << "\t--setOwnTeamColor {red/blue} [required]" << endl;
	stream << "\t--setOwnClientNumber {value between 10 and 16} [required]" << endl;
	stream << "\t--disableHardwareCheck [optional]" << endl;
	stream << "\t--disableRouteServer [optional]" << endl;
	stream << "\t--routeServerPort {value between 1 and 65 536} [optional]" << endl;
	stream << "\t--disableLogging [optional]" << endl;

	return stream.str();
}

vector<string> InputArgumentParser::convertArguments(int argc, char **argv)
{
	vector<string> arguments;
	arguments.reserve(argc);

	for (int i=0; i < argc; i++)
	{
		string currentArgument(argv[i]);
		arguments.push_back(currentArgument);
	}

	return arguments;
}

void InputArgumentParser::parseTeamColor(list<string> &arguments)
{
	if (arguments.empty())
	{
		m_valid = false;
		return;
	}

	string teamColor = arguments.front();
	arguments.pop_front();

	if (teamColor == "red")
		m_ownTeamColor = TeamColorRed;
	else if (teamColor == "blue")
		m_ownTeamColor = TeamColorBlue;
	else
		m_valid = false;
}

void InputArgumentParser::parseClientNumber(list<string> &arguments)
{
	if (arguments.empty())
	{
		m_valid = false;
		return;
	}

	string value = arguments.front();
	arguments.pop_front();
	m_ownClientNumber = atoi(value.c_str());

	if ((m_ownClientNumber < 11)||(m_ownClientNumber > 15))
	{
		m_valid = false;
		return;
	}
}

void InputArgumentParser::parseDisableHardwareCheck()
{
	m_disableHardwareCheck = true;
}

void InputArgumentParser::parseDisableRouteServer()
{
	m_disableRouteServer = true;
}

void InputArgumentParser::parseRouteServerPort(list<std::string> &arguments)
{
	if (arguments.empty())
	{
		m_valid = false;
		return;
	}

	string serverPort = arguments.front();
	arguments.pop_front();
	m_routeServerPort = atoi(serverPort.c_str());

	if ((m_routeServerPort < 1)||(m_routeServerPort > 65536))
	{
		m_valid = false;
		return;
	}
}

void InputArgumentParser::parseDisableLogging()
{
	m_disableLogging = true;
}

