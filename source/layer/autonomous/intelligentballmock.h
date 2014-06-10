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

		virtual void update();
		virtual Common::Geometry::Angle getRotation() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;
		virtual Common::Geometry::Point getPosition() const;
		virtual double getVelocity() const;
		virtual bool isMoving() const;
		virtual Abstraction::FieldSide getMovingDirection() const;
		virtual Abstraction::FieldSide getCurrentFieldSide() const;
		virtual double getShootingLineCoveragePercent(ObstacleFetcher &obstacles, Common::Geometry::Point &target) const;

		void setPosition(Common::Geometry::Point position);
		void setRotation(Common::Geometry::Angle angle);
		void setIsMoving(bool value);
		void setCurrentFieldSide(Layer::Abstraction::FieldSide fieldSide);
		void setMovingDirection(Layer::Abstraction::FieldSide fieldSide);
		void setObstacle(Common::Geometry::Circle const &obstacle);

	private:
		Abstraction::BallMock m_ball;
		bool m_isMoving;
		Abstraction::FieldSide m_currentFieldSide;
		Abstraction::FieldSide m_movingDirection;
		Common::Geometry::Circle m_obstacle;
	};
}
}
}

#endif
