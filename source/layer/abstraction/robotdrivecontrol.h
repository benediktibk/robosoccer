#ifndef ROBOSOCCER_LAYER_ABSTRACTION_ROBOTDRIVECONTROL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_ROBOTDRIVECONTROL_H

#include "common/geometry/point.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
}
namespace Other
{
	class PIDController;
}
namespace Geometry
{
	class Pose;
}
}
namespace Layer
{
namespace Abstraction
{
	class RobotDriveControl
	{
	public:
		RobotDriveControl(Common::Time::Watch const &watch);
		~RobotDriveControl();

		void evaluate(Common::Geometry::Pose const &current, Common::Geometry::Point const &target, double &translationSpeed, double &rotationSpeed);
		void reset(Common::Geometry::Pose const &start);

	private:
		Common::Other::PIDController *m_rotationController;
		Common::Other::PIDController *m_translationController;
		Common::Geometry::Point m_startPosition;
	};
}
}
}

#endif
