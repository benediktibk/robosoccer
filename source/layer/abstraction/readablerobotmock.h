#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTMOCK_H

#include "layer/abstraction/readablerobot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ReadableRobotMock :
			public ReadableRobot
	{
	public:
		virtual Common::Geometry::OrientedPosition getPosition();
		virtual Common::Geometry::Circle createObstacle();
	};
}
}
}

#endif

