#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALLMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALLMOCK_H

#include "layer/abstraction/ball.h"

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
		virtual Common::Geometry::Point getPosition();
		virtual Common::Geometry::Circle getObstacle();
	};
}
}
}

#endif

