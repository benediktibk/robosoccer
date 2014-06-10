#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKER_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKER_H

#include "common/routing/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
}
}
namespace Layer
{
namespace Main
{
	class FieldPositionChecker :
			public Common::Routing::FieldPositionChecker
	{
	public:
		bool isPointInsideLeftGoalZone(Common::Geometry::Point const &position) const;
		bool isPointInsideRightGoalZone(Common::Geometry::Point const &position) const;
	};
}
}
}

#endif


