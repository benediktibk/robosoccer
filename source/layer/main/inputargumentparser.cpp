#include "layer/main/inputargumentparser.h"
#include <stdlib.h>
#include <sstream>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

InputArgumentParser::InputArgumentParser(vector<string> const &arguments)
{
	if (arguments.size() != 5)
	{
		m_valid = false;
		return;
	}

	if ((arguments[1] != "--setOwnTeamColor") && (arguments[3] != "--setOwnClientNumber"))
	{
		m_valid = false;
		return;
	}

	string value = arguments[4];
	m_ownClientNumber = atoi(value.c_str());
	if ((m_ownClientNumber < 11)||(m_ownClientNumber > 15))
	{
		m_valid = false;
		return;
	}

	m_valid = true;
	if (arguments[2] == "red")
		m_ownTeamColor = TeamColorRed;
	else if (arguments[2] == "blue")
		m_ownTeamColor = TeamColorBlue;
	else
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

string InputArgumentParser::usage() const
{
	stringstream stream;

	stream << "usage: " << endl;
	stream << "All arguments in correct order are required!" << endl;
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
