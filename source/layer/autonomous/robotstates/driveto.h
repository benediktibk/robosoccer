#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETO_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "common/geometry/pose.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;
}
namespace Time
{
	class Watch;
	class StopWatch;
}
namespace Routing
{
	class Router;
	class Route;
}
}
namespace Layer
{
namespace Autonomous
{
	class ObstacleFetcher;
	class ObstacleSource;

	class DriveTo :
			public RobotState
	{
	public:
		DriveTo(Abstraction::ControllableRobot &robot,
				const Common::Geometry::Pose &target,
				const Common::Routing::Router &router,
				Common::Time::Watch const &watch,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher &obstacleFetcher, ObstacleSource &autonomousRobot,
				bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles);
		virtual ~DriveTo();

		virtual bool reachedTarget() const;
		virtual RobotState* nextState(bool movementStopped);
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const;
		virtual void update(bool movementStopped);

		size_t getRoutePointsCount() const;

	private:
		bool setOrdersForIntermediatePointAndGetOrderSet(bool movementStopped);
		void updateRoute();
		void updateRouteForTarget();
		const Common::Geometry::Point &getNextTargetPoint() const;
		bool isRouteFeasible(const std::vector<Common::Geometry::Circle> &obstacles) const;
		std::vector<Common::Geometry::Circle> modifyObstacles(const std::vector<Common::Geometry::Circle> &obstacles, double growFactor) const;
		std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRangeDependentOnFlags(const Common::Geometry::Point &robotPoint, double distance) const;
		void clearRoute();
		void resetAllMovementFlags();
		void prepareLastRouteSegmentForDrivingSlowly();
		void logRoute();
		void logCurrentPose();

	private:
		const double m_precisionPosition;
		const double m_precisionOrientationInitial;
		const double m_precisionOrientationFinal;
		bool m_initialRotationReached;
		bool m_initialRotationStarted;
		bool m_driveStarted;
		bool m_finalRotationReached;
		bool m_finalRotationStarted;
		bool m_movementStopUsed;
		bool m_ignoreBall;
		bool m_driveSlowlyAtTheEnd;
		bool m_ignoreGoalObstacles;
		Common::Geometry::Pose m_target;
		Common::Routing::Router const &m_router;
		Common::Time::StopWatch *m_watchDog;
		Common::Routing::Route *m_currentRoute;
		ObstacleFetcher &m_obstacleFetcher;
		ObstacleSource &m_autonomousRobot;
	};
}
}
}

#endif
