#include "layer/main/inputargumentparser.h"
#include <stdlib.h>
#include <sstream>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

InputArgumentParser::InputArgumentParser(vector<string> const &arguments) :
	m_valid(true)
{
	list<string> argumentsList(arguments.begin() + 1, arguments.end());
	bool teamColorSet = false;
	bool clientNumberSet = false;

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
		else
			m_valid = false;
	}
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

string InputArgumentParser::usage() const
{
	stringstream stream;

	stream << "usage: " << endl;
	stream << "\t--setOwnTeamColor <{red,blue}>" << endl;
	stream << "\t--setOwnClientNumber <{10 < clientNr < 16}>" << endl;

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
