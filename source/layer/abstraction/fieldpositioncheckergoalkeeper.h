#ifndef ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERGOALKEEPER_H
#define ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERGOALKEEPER_H

#include "layer/abstraction/fieldpositionchecker.h"
#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class FieldPositionCheckerGoalkeeper :
			public FieldPositionChecker
	{
	public:
		FieldPositionCheckerGoalkeeper();

		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;
		bool isPointInsideDangerZone(Common::Geometry::Point const &ballPosition) const;

		void setFieldSide(Abstraction::FieldSide fieldSide);

	private:
		Abstraction::FieldSide m_fieldSide;
	};
}
}
}

#endif
