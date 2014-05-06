#ifndef ROBOSOCCER_LAYER_ABSTRACTION_ROBOTTURNCONTROL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_ROBOTTURNCONTROL_H

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
	class PIDController;
}
namespace Geometry
{
	class Angle;
}
namespace Time
{
	class Watch;
}
}
namespace Layer
{
namespace Abstraction
{
	class RobotTurnControl
	{
	public:
		RobotTurnControl(Common::Time::Watch const &watch);
		~RobotTurnControl();

		double evaluate(Common::Geometry::Angle const &currentOrientation, Common::Geometry::Angle const &targetOrientation);
		void reset();

	private:
		Common::Other::PIDController *m_controller;
	};
}
}
}

#endif