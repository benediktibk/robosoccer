#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALLMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALLMOCK_H

#include "layer/abstraction/ball.h"
#include "common/geometry/point.h"

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

		virtual Common::Geometry::Point getPosition() const;
		virtual Common::Geometry::Angle getRotation() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual double getVelocity() const;

		void setPosition(Common::Geometry::Point position);
		void setVelocity(double value);

	private:
		Common::Geometry::Point m_position;
		double m_velocity;
	};
}
}
}

#endif


