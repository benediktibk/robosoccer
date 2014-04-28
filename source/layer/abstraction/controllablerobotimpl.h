#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H

#include "layer/abstraction/controllablerobot.h"
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
	class ControllableRobotImpl :
			public ControllableRobot
	{
	public:
		ControllableRobotImpl(unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color);
		~ControllableRobotImpl();
		virtual Common::Geometry::Pose getPosition() const;
		virtual Common::Geometry::Circle createObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(const Common::Geometry::Point &position);
		virtual bool kick(unsigned int force, double distanceToBall);
		virtual void turn(const Common::Geometry::Angle &absoluteAngle);

	private:
		RoboControl *m_robot;
	};
}
}
}

#endif


