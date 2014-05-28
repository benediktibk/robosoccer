#include "layer/main/inputargumentparser.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

InputArgumentParser::InputArgumentParser(vector<string> const &arguments)
{
	if (arguments.size() != 3)
	{
		m_valid = false;
		return;
	}

	if (arguments[1] != "--setOwnTeamColor")
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
