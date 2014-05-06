#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLMOCK_H

#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/ballmock.h"
#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class IntelligentBallMock :
			public IntelligentBall
	{
	public:
		IntelligentBallMock();

		virtual Common::Geometry::Angle getRotation() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual Common::Geometry::Point getPosition() const;
		virtual double getVelocity() const;
		virtual bool isMoving() const;
		virtual Abstraction::FieldSide getMovingDirection() const;
		virtual Abstraction::FieldSide getCurrentFieldSide() const;

		void setPosition(Common::Geometry::Point position);
		void setRotation(Common::Geometry::Angle angle);
		void setIsMoving(bool value);
		void setCurrentFieldSide(Layer::Abstraction::FieldSide fieldSide);
		void setMovingDirection(Layer::Abstraction::FieldSide fieldSide);

	private:
		Abstraction::BallMock m_ball;
		bool m_isMoving;
		Abstraction::FieldSide m_currentFieldSide;
		Abstraction::FieldSide m_movingDirection;

	};
}
}
}

#endif
