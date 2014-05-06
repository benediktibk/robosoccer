#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H

#include "layer/abstraction/controllablerobot.h"
#include "layer/abstraction/teamcolor.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"

class RoboControl;

namespace KogniMobil
{
	class RTDBConn;
}

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
}
}
namespace Layer
{
namespace Abstraction
{
	class RobotTurnControl;
	class RobotDriveControl;

	class ControllableRobotImpl :
			public ControllableRobot
	{
	private:
		enum State
		{
			StateStop,
			StateTurning,
			StateDriving
		};

	public:
		ControllableRobotImpl(unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color, Common::Time::Watch const &watch);
		~ControllableRobotImpl();

		virtual Common::Geometry::Pose getPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(const Common::Geometry::Point &position);
		virtual bool kick(unsigned int force);
		virtual void turn(const Common::Geometry::Angle &absoluteAngle);
		virtual void stop();
		virtual void update();

		Common::Geometry::Angle getOrientation() const;
		Common::Geometry::Point getPosition() const;

	private:
		void switchInto(State state);

	private:
		RoboControl *m_robot;
		RobotTurnControl *m_turnControl;
		RobotDriveControl *m_driveControl;
		State m_state;
		Common::Geometry::Angle m_turnTarget;
		Common::Geometry::Point m_driveTarget;
	};
}
}
}

#endif


