#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALL_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Angle;
	class Circle;
	class Point;
}
}
namespace Layer
{
namespace Abstraction
{
	class Ball;
}
namespace Autonomous
{
	class IntelligentBall
	{
	public:
		IntelligentBall();
		virtual ~IntelligentBall();

		Common::Geometry::Angle getRotation() const;
		Common::Geometry::Circle getObstacle() const;
		virtual Common::Geometry::Point getPosition() const;
		double getVelocity() const;
		bool isMoving() const;
		Abstraction::FieldSide getMovingDirection() const;

	private:
		Abstraction::Ball *m_ball;
	};
}
}
}
#endif
