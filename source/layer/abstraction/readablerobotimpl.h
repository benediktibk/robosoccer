#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTIMPL_H

#include "layer/abstraction/readablerobot.h"
#include "teamcolor.h"

class RoboControl;

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
	class ReadableRobotImpl :
			public ReadableRobot
	{
	public:
		ReadableRobotImpl(unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color);
		~ReadableRobotImpl();

		virtual Common::Geometry::OrientedPosition getPosition() const;
		virtual Common::Geometry::Circle createObstacle() const;

	private:
		RoboControl *m_robot;
	};
}
}
}

#endif


