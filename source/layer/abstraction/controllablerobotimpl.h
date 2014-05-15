#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H

#include "layer/abstraction/controllablerobot.h"
#include "layer/abstraction/teamcolor.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include "common/geometry/pose.h"

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
	class StopWatch;
}
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class RobotDriveControl;

	class ControllableRobotImpl :
			public ControllableRobot
	{
	private:
		enum State
		{
			StateStop,
			StateTurning,
			StateDrivingShort,
			StateDrivingLong,
			StateKick
		};

	public:
		ControllableRobotImpl(unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color, Common::Time::Watch const &watch, Common::Logging::Logger &logger);
		~ControllableRobotImpl();

		virtual Common::Geometry::Pose getPose() const;
		virtual Common::Geometry::Pose getPoseRaw() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(const Common::Geometry::Point &position);
		virtual void kick(unsigned int force);
		virtual void turn(const Common::Geometry::Angle &absoluteAngle);
		virtual void stop();
		virtual void update();
		virtual bool isMoving() const;

		Common::Geometry::Angle getOrientation() const;
		Common::Geometry::Angle getOrientationRaw() const;
		Common::Geometry::Point getPosition() const;

	private:
		void switchInto(State state);
		void setSpeed(double translationSpeed, double rotationSpeed);
		void determineIsDrivingForwardForGoTo(Common::Geometry::Point const &target);
		void determineIsDrivingForwardForTurning(Common::Geometry::Angle const &target);
		void logState(State state);
		void logIsDrivingForward();
		void logPosition(std::string const &message, Common::Geometry::Point const &position);
		void logOrientation(std::string const &message, Common::Geometry::Angle const &orientation);
		void log(std::string const &message);

	private:
		RoboControl *m_robot;
		RobotDriveControl *m_driveShortControl;
		RobotDriveControl *m_driveLongControl;
		State m_state;
		Common::Geometry::Point m_driveTarget;
		Common::Geometry::Angle m_turnTarget;
		double m_translationSpeed;
		double m_rotationSpeed;
		Common::Geometry::Pose m_lastPoseReceived;
		Common::Time::StopWatch *m_loopTimeWatch;
		bool m_isDrivingFoward;
		Common::Time::StopWatch *m_watchDogEnd;
		Common::Time::StopWatch *m_watchDogRestart;
		Common::Logging::Logger &m_logger;
		const unsigned int m_deviceId;
		bool m_turnStarted;
	};
}
}
}

#endif
