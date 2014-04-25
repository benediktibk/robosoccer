#ifndef ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H
#define ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H

#include "layer/abstraction/fieldside.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class OrientedPosition;
}
}
namespace Layer
{
namespace Main
{
class TargetPositionFetcher
{
public:
	TargetPositionFetcher();

	void setFieldSide(Layer::Abstraction::FieldSide fieldside);

	Common::Geometry::OrientedPosition getStartPosition() const;
	std::vector<Common::Geometry::OrientedPosition> getEnemyGoalPosition() const;
	Common::Geometry::OrientedPosition getOwnGoalPosition() const;
	Common::Geometry::OrientedPosition getPenaltyPositionKicker() const;

private:
	Layer::Abstraction::FieldSide m_fieldside;

};
}
}
}

#endif // ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H


