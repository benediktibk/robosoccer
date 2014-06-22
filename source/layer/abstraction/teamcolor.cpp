#include "layer/abstraction/teamcolor.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

ostream &operator<<(ostream &stream, const TeamColor &teamColor)
{
	switch(teamColor)
	{
	case TeamColorBlue:
		stream << "blue";
		break;
	case TeamColorRed:
		stream << "red";
		break;
	}

	return stream;
}
