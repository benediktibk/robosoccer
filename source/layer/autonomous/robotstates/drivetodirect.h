#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECT_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECT_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "common/geometry/pose.h"

namespace RoboSoccer
{
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
				Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);

		virtual bool reachedTarget() const;
		virtual bool isEquivalentToDriveToDirect(const Common::Geometry::Pose &target);
		virtual bool isEquivalentToDriveTo(const std::vector<Common::Geometry::Pose> &targets);
		virtual void update();

		Common::Geometry::Pose const& getTarget() const;
		double getPrecisionInitialRotation() const;
		double getPrecisionDriving() const;
		double getPrecisionFinalRotation() const;
		bool hasMovementStarted() const;

	protected:
		virtual void updateInternal() = 0;

	private:
		const Common::Geometry::Pose m_target;
		const double m_precisionInitialRotation;
		const double m_precisionDriving;
		const double m_precisionFinalRotation;
		bool m_movementStarted;
	};
}
}
}

#endif


