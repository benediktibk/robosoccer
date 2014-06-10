#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALLMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALLMOCK_H

#include "layer/abstraction/ball.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class BallMock :
			public Ball
	{
	public:
		BallMock();

		virtual void update();
		virtual Common::Geometry::Point getPosition() const;
		virtual Common::Geometry::Angle getRotation() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual double getVelocity() const;

		void setRotation(Common::Geometry::Angle value);
		void setPosition(Common::Geometry::Point position);
		void setVelocity(double value);
		void setObstacle(Common::Geometry::Circle const &obstacle);

	private:
		Common::Geometry::Point m_position;
		double m_velocity;
		Common::Geometry::Angle m_rotation;
		Common::Geometry::Circle m_obstacle;
	};
}
}
}

#endif


