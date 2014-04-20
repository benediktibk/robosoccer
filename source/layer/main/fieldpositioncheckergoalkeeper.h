#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPER_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPER_H

#include "common/routing/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class FieldPositionCheckerGoalkeeper :
			public Common::Routing::FieldPositionChecker
	{
	public:
		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;
	};
}
}
}

#endif


