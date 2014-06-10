#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALLIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALLIMPL_H

#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"

class RawBall;

namespace KogniMobil
{
	class RTDBConn;
}

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class BallImpl :
			public Ball
	{
	public:
		BallImpl(KogniMobil::RTDBConn &dataBase);
		virtual ~BallImpl();
		virtual void update();
		virtual Common::Geometry::Point getPosition() const;
		virtual Common::Geometry::Angle getRotation() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual double getVelocity() const;

	private:
		RawBall *m_ball;
		double m_velocity;
		Common::Geometry::Angle m_orientation;
		Common::Geometry::Point m_position;

	};
}
}
}

#endif


