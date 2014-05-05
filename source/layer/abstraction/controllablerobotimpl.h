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
		virtual Common::Geometry::Pose getPose() const;
		virtual Common::Geometry::Circle createObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(const Common::Geometry::Point &position);
		virtual bool kick(unsigned int force);
		virtual void turn(const Common::Geometry::Angle &absoluteAngle);
		virtual void stop();

		Common::Geometry::Angle getOrientation() const;
		Common::Geometry::Point getPosition() const;

	private:
		RoboControl *m_robot;
	};
}
}
}

#endif


