#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPER_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPER_H

#include "common/routing/fieldpositionchecker.h"
#include "layer/abstraction/fieldside.h"

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
		FieldPositionCheckerGoalkeeper();

		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;

		void setTeamSide(Abstraction::FieldSide fieldSide);

	private:
		Abstraction::FieldSide m_fieldSide;
	};
}
}
}

#endif


