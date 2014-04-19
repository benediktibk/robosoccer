#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTIMPL_H

#include "layer/abstraction/readablerobot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ReadableRobotImpl :
			public ReadableRobot
	{
	public:
		ReadableRobotImpl();

		virtual Common::Geometry::OrientedPosition getPosition();
		virtual Common::Geometry::Circle createObstacle();

	private:
	};
}
}
}

#endif


