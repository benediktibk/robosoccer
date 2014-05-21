#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLIMPL_H

#include "intelligentball.h"
namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class IntelligentBallImpl :
			public IntelligentBall
	{
	public:
		IntelligentBallImpl(Abstraction::Ball const &ball);

		virtual Common::Geometry::Angle getRotation() const;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual Common::Geometry::Point getPosition() const;
		virtual double getVelocity() const;
		virtual bool isMoving() const;
		virtual Abstraction::FieldSide getMovingDirection() const;
		virtual Abstraction::FieldSide getCurrentFieldSide() const;
		virtual double getShootingLineCoveragePercent(ObstacleFetcher &obstacles, Common::Geometry::Point &target) const;
	private:
		Abstraction::Ball const &m_ball;
	};
}
}
}

#endif


