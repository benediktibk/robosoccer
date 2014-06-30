#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTIMPL_H

#include "layer/abstraction/readablerobot.h"
#include "teamcolor.h"
#include "common/geometry/pose.h"

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

		virtual Common::Geometry::Pose getPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual void update();

	private:
		RoboControl *m_robot;
		Common::Geometry::Pose m_pose;
	};
}
}
}

#endif


