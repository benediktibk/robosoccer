#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERMOCK_H

#include "layer/autonomous/obstaclefetcher.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ObstacleFetcherMock :
			public ObstacleFetcher
	{
	public:
		ObstacleFetcherMock();

		virtual void addSource(ObstacleSource const &source);
		virtual void defineBall(ObstacleSource const &source);
		virtual std::vector<Common::Geometry::Circle> getAllObstacles() const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMe(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndBall(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndGoalObstacles(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndBallInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndGoalObstaclesInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRangeDependentOnDriveMode(ObstacleSource const &me,
				const Common::Geometry::Point &ownPosition, double distance, bool ignoreBall, bool ignoreGoalObstacles) const;

		void setAllObstacles(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMe(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMeInRange(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMeAndBallInRange(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMeAndGoalObstaclesInRange(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMeDependentOn(std::vector<Common::Geometry::Circle> const &obstacles);

	private:
		std::vector<Common::Geometry::Circle> m_allObstacles;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMe;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeAndBall;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeAndGoalObstacles;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeInRange;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeAndBallInRange;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeAndGoalObstaclesInRange;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeDependentOnDriveMode;
	};
}
}
}

#endif
