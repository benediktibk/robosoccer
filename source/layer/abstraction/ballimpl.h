#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALLIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALLIMPL_H

#include "layer/abstraction/ball.h"


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

		virtual Common::Geometry::OrientedPosition getPosition() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual double getVelocity() const;
	private:
		RawBall *m_ball;
	};
}
}
}

#endif


