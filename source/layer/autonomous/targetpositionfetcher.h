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
namespace Autonomous
{
	class IntelligentBall;

	class TargetPositionFetcher
	{
	public:
		TargetPositionFetcher();

		void setFieldSide(Abstraction::FieldSide fieldSide);

		Common::Geometry::Pose getStartPositionGoalkeeper() const;
		Common::Geometry::Pose getStartPositionPlayerOneOffensive() const;
		Common::Geometry::Pose getStartPositionPlayerTwoOffensive() const;
		Common::Geometry::Pose getStartPositionPlayerOneDefensive() const;
		Common::Geometry::Pose getStartPositionPlayerTwoDefensive() const;

		std::vector<Common::Geometry::Point> getEnemyGoalPosition() const;
		Common::Geometry::Pose getOwnGoalPosition(const IntelligentBall &ball) const;

		Common::Geometry::Pose getPenaltyPositionPrepareKicker() const;
		Common::Geometry::Pose getPenaltyPositionKicker(const IntelligentBall &ball) const;
		Common::Geometry::Pose getPenaltyPositionGoalie(const IntelligentBall &ball) const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionsUnusedPlayerOne() const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionsUnusedPlayerTwo() const;

	private:
		Common::Geometry::Pose getOwnGoalPosition(Abstraction::FieldSide fieldSide, const IntelligentBall &ball) const;
		std::vector<Common::Geometry::Point> getEnemyGoalPosition(Abstraction::FieldSide fieldSide) const;

		Common::Geometry::Pose mirrorPointDependentOnFieldSide(Abstraction::FieldSide fieldSide, Common::Geometry::Point pointFieldSideRight) const;
		Common::Geometry::Pose getGoaliePositionUsingStandardTactic(Abstraction::FieldSide fieldSide, const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const;
		Common::Geometry::Pose getGoaliePositionUsingStandardTactic(const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const;

	private:
		Abstraction::FieldSide m_fieldSide;

	};
}
}
}

#endif
