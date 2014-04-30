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
		IntelligentBallImpl();

		virtual Common::Geometry::Angle getRotation() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual Common::Geometry::Point getPosition() const;
		virtual double getVelocity() const;
		virtual bool isMoving() const;
		virtual Abstraction::FieldSide getMovingDirection() const;

	private:
		Abstraction::Ball *m_ball;
	};
}
}
}

#endif


