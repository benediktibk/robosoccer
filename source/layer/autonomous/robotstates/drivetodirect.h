#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECT_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECT_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "common/geometry/pose.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
	class StopWatch;
}
}
namespace Layer
{
namespace Autonomous
{
	class DriveToDirect :
			public RobotState
	{
	public:
		DriveToDirect(
				Abstraction::ControllableRobot &robot,
				Common::Geometry::Pose const &target,
				Common::Time::Watch const &watch,
				Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);
		virtual ~DriveToDirect();

		virtual bool reachedTarget() const;
		virtual RobotState* nextState(bool movementStopped);
		virtual bool isEquivalentToDriveToDirect(const Common::Geometry::Pose &target) const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const;

	protected:
		virtual void updateInternal(bool movementStopped);

	private:
		const double m_precisionPosition;
		const double m_precisionOrientationInitial;
		const double m_precisionOrientationFinal;
		bool m_initialRotationReached;
		bool m_initialRotationStarted;
		bool m_positionReached;
		bool m_driveStarted;
		bool m_finalRotationReached;
		bool m_finalRotationStarted;
		Common::Geometry::Pose m_target;
		Common::Time::StopWatch *m_watchDog;
	};
}
}
}

#endif