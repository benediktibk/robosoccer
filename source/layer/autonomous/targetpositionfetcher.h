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
	class Angle;
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
		Common::Geometry::Point getPointBehindBallInMovingDirection(const IntelligentBall &ball, double distanceToBall) const;
		Common::Geometry::Pose getTargetBehindBall(const IntelligentBall &ball, double distanceToBall) const;
		std::vector<Common::Geometry::Pose> getAlternativeRobotPositionAtBallHeightAggressiveMode(const IntelligentBall &ball,const Common::Geometry::Point &currentAlternativeRobotPosition) const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionsUnusedPlayerOne() const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionsUnusedPlayerTwo() const;
		std::vector<Common::Geometry::Pose> getPositionToDriveOnBall(const IntelligentBall &ball) const;
		Common::Geometry::Angle getOrientationToEnemyGoal() const;

	private:
		std::vector<Common::Geometry::Point> getEnemyGoalPosition(Abstraction::FieldSide fieldSide) const;

		Common::Geometry::Pose mirrorPointDependentOnFieldSide(Abstraction::FieldSide fieldSide, Common::Geometry::Point pointFieldSideRight) const;
		Common::Geometry::Pose getGoaliePositionUsingEstimatedIntersectPoint(Abstraction::FieldSide fieldSide, const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const;
		Common::Geometry::Pose getGoaliePositionUsingIntersectWithGoalCenter(Abstraction::FieldSide fieldSide, const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const;
		Common::Geometry::Pose getGoaliePositionUsingYCoordinateFollowing(const IntelligentBall &ball, double xPositionGoalKeeper) const;

	private:
		Abstraction::FieldSide m_fieldSide;

	};
}
}
}

#endif
