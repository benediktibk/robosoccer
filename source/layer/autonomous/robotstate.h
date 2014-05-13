#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATE_H

#include <string>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Pose;
}
}
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
		virtual bool isEquivalentToDriveTo(Common::Geometry::Point const &target) const;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const = 0;

		Abstraction::ControllableRobot& getRobot();
		Abstraction::ControllableRobot const& getRobot() const;

	private:
		//forbid copies
		RobotState(RobotState const &rhs) : m_robot(rhs.m_robot) { }
		void operator=(RobotState const&) { }

	private:
		Abstraction::ControllableRobot &m_robot;
	};
}
}
}

#endif


