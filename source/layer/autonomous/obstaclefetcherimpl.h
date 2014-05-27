#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERIMPL_H

#include "layer/autonomous/obstaclefetcher.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ObstacleFetcherImpl :
			public ObstacleFetcher
	{
	public:
		ObstacleFetcherImpl();
		~ObstacleFetcherImpl();

		virtual void addSource(ObstacleSource const &source);
		virtual void defineBall(ObstacleSource const &source);
		virtual std::vector<Common::Geometry::Circle> getAllObstacles() const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMe(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndBall(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndBallInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;

	private:
		std::vector<Common::Geometry::Circle> filterByDistance(
				std::vector<Common::Geometry::Circle> const &candidates, Common::Geometry::Point const &ownPosition, double distance) const;
		bool isInRange(Common::Geometry::Point const &ownPosition, double distance, Common::Geometry::Circle const &circle) const;

	private:
		std::vector<ObstacleSource const *> m_sources;
		ObstacleSource const *m_ball;
	};
}
}
}

#endif


