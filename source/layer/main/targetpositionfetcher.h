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
namespace Abstraction
{
	class Ball;
}
namespace Main
{
class TargetPositionFetcher
{
public:
	TargetPositionFetcher();

	void setFieldSide(Abstraction::FieldSide fieldside);

	Common::Geometry::OrientedPosition getStartPosition() const;
	std::vector<Common::Geometry::OrientedPosition> getEnemyGoalPosition() const;
	Common::Geometry::OrientedPosition getOwnGoalPosition(const Abstraction::Ball &ball) const;
	Common::Geometry::OrientedPosition getPenaltyPositionKicker(const Abstraction::Ball &ball) const;

private:
	Abstraction::FieldSide m_fieldside;

};
}
}
}

#endif // ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H


