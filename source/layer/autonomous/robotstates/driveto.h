#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETO_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "layer/autonomous/robotstates/drivemode.h"
#include "common/geometry/pose.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;
	class Compare;
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
				const std::vector<Common::Geometry::Pose> &targets,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource,
				DriveMode driveMode);
		virtual ~DriveTo();

		virtual bool reachedTarget() const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target);
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target);

		size_t getRoutePointsCount() const;
		Common::Geometry::Compare getPositionCompare() const;
		Common::Geometry::Compare getInitialRotationCompare() const;
		Common::Geometry::Compare getFinalRotationCompare() const;
		std::vector<Common::Geometry::Pose> const& getTargets() const;
		Common::Routing::Router const& getRouter() const;
		ObstacleFetcher const& getObstacleFetcher() const;
		ObstacleSource const& getOwnObstacleSource() const;
		DriveMode getDriveMode() const;
		Common::Routing::Route const& getCurrentRoute() const;

	protected:
		bool updateRouteIfNecessary();
		void setRoute(const Common::Routing::Route &route);
		RobotState* nextStateWithRouteUpdate();

	private:
		void calculateNewRoute();
		const Common::Geometry::Point &getNextTargetPoint() const;
		bool isRouteFeasible(const std::vector<Common::Geometry::Circle> &obstacles) const;
		std::vector<Common::Geometry::Circle> modifyObstacles(const std::vector<Common::Geometry::Circle> &obstacles, double growFactor) const;
		void clearRoute();
		void prepareLastRouteSegmentForDrivingSlowly();
		void logRoute();
		void logCurrentPose();

	private:
		const double m_precisionPosition;
		const double m_precisionOrientationInitial;
		const double m_precisionOrientationFinal;
		const DriveMode m_driveMode;
		const std::vector<Common::Geometry::Pose> m_targets;
		Common::Routing::Router const &m_router;
		ObstacleFetcher const &m_obstacleFetcher;
		ObstacleSource const &m_ownObstacleSource;
		Common::Routing::Route *m_currentRoute;
	};
}
}
}

#endif
