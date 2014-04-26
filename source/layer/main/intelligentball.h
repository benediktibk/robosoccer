#ifndef ROBOSOCCER_LAYER_MAIN_INTELLIGENTBALL_H
#define ROBOSOCCER_LAYER_MAIN_INTELLIGENTBALL_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class OrientedPosition;
	class Circle;
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
	class IntelligentBall
	{
	public:
		IntelligentBall();
		Common::Geometry::OrientedPosition getPosition() const;
		Common::Geometry::Circle getObstacle() const;
		double getVelocity() const;
		bool isMoving(double velocity) const;
		Abstraction::FieldSide getMovingDirection(Common::Geometry::OrientedPosition position) const;
	private:
		Abstraction::Ball *m_ball;
	};
}
}
}
#endif
