#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPER_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPER_H

#include "layer/main/fieldpositionchecker.h"
#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class FieldPositionCheckerGoalkeeper :
			public FieldPositionChecker
	{
	public:
		FieldPositionCheckerGoalkeeper();

		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;

		void setFieldSide(Abstraction::FieldSide fieldSide);

	private:
		Abstraction::FieldSide m_fieldSide;
	};
}
}
}

#endif
