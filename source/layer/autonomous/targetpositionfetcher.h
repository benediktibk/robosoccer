#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TARGETPOSITIONFETCHER_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TARGETPOSITIONFETCHER_H

#include "layer/abstraction/fieldside.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Pose;
	class Point;
}
}
namespace Layer
{
namespace Abstraction
{
	class Ball;
}
namespace Autonomous
{
	class TargetPositionFetcher
	{
	public:
		TargetPositionFetcher();

		void setFieldSide(Abstraction::FieldSide fieldside);

		Common::Geometry::Pose getStartPositionGoalkeeper() const;
		Common::Geometry::Pose getStartPositionPlayerOneOffensive() const;
		Common::Geometry::Pose getStartPositionPlayerTwoOffensive() const;
		Common::Geometry::Pose getStartPositionPlayerOneDefensive() const;
		Common::Geometry::Pose getStartPositionPlayerTwoDefensive() const;

		std::vector<Common::Geometry::Point> getEnemyGoalPosition() const;
		Common::Geometry::Pose getOwnGoalPosition(const Abstraction::Ball &ball) const;
		Common::Geometry::Pose getPenaltyPositionKicker(const Abstraction::Ball &ball) const;

	private:
		Common::Geometry::Pose mirrorPointDependentOnFieldSide(Common::Geometry::Point pointRightSide) const;

	private:
		Abstraction::FieldSide m_fieldside;

	};
}
}
}

#endif