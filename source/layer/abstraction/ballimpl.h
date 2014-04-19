#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALLIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALLIMPL_H

#include "layer/abstraction/ball.h"

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
		BallImpl();

		virtual Common::Geometry::Point getPosition();
		virtual Common::Geometry::Circle getObstacle();
	};
}
}
}

#endif


