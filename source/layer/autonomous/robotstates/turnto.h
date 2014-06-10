#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_TURNTO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_TURNTO_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "common/geometry/point.h"

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
	class TurnTo :
			public RobotState
	{
	public:
		TurnTo(
				Abstraction::ControllableRobot &robot, Common::Geometry::Point const &target,
				RobotState *followingState, Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);
		virtual ~TurnTo();

		virtual bool reachedTarget() const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target);
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target);
		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;
		virtual void update();

	private:
		Common::Geometry::Angle calculateTargetOrientation() const;

	private:
		Common::Geometry::Point m_target;
		RobotState *m_followingState;
		bool m_targetAlreadySet;
	};
}
}
}

#endif
