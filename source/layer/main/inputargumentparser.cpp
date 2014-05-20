#include "layer/main/inputargumentparser.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

InputArgumentParser::InputArgumentParser(vector<string> const &arguments)
{

	if (string Argument(arguments,17) == "--SetOwnTeamColor ")
	{
		m_valid = true;
		switch (InputArgumentParser(arguments, 17, 4))
		{
			case "red": m_ownTeamColor = TeamColorRed;
			case "blue": m_ownTeamColor = TeamColorBlue;
	}
	}
	else {
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


