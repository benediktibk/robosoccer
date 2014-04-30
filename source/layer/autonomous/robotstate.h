#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATE_H

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ControllableRobot;
}
namespace Autonomous
{
	class RobotState
	{
	public:
		RobotState(Abstraction::ControllableRobot &robot);
		virtual ~RobotState();

		virtual bool reachedTarget() const = 0;
		virtual bool cantReachTarget() const = 0;
		virtual RobotState* nextState() = 0;
		virtual void update() = 0;

		Abstraction::ControllableRobot& getRobot();
		Abstraction::ControllableRobot const& getRobot() const;

	private:
		Abstraction::ControllableRobot &m_robot;
	};
}
}
}

#endif


