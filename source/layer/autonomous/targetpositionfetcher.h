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

		std::vector<Common::Geometry::Pose> getStartPositionsGoalkeeper() const;
		std::vector<Common::Geometry::Pose> getStartPositionsPlayerOneOffensive() const;
		std::vector<Common::Geometry::Pose> getStartPositionsPlayerTwoOffensive() const;
		std::vector<Common::Geometry::Pose> getStartPositionsPlayerOneDefensive() const;
		std::vector<Common::Geometry::Pose> getStartPositionsPlayerTwoDefensive() const;

		std::vector<Common::Geometry::Point> getEnemyGoalPositions() const;
		std::vector<Common::Geometry::Point> getOwnGoalPositions() const;
		double getDistanceToOwnGroundLine(const Common::Geometry::Point &position) const;

		Common::Geometry::Pose getTargetForGoalkeeper(const IntelligentBall &ball) const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionGoalie(const IntelligentBall &ball) const;

		std::vector<Common::Geometry::Pose> getPenaltyPositionsPrepareKicker() const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionKicker(const IntelligentBall &ball) const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionsUnusedPlayerOne() const;
		std::vector<Common::Geometry::Pose> getPenaltyPositionsUnusedPlayerTwo() const;

		std::vector<Common::Geometry::Pose> getAlternativeRobotPositionsBehindBallAggressiveMode(const IntelligentBall &ball,const Common::Geometry::Point &positionRobotOne) const;
		std::vector<Common::Geometry::Pose> getTargetsBehindBall(const IntelligentBall &ball) const;
		std::vector<Common::Geometry::Pose> getTargetsBehindBallAlternativeRobot(const IntelligentBall &ball) const;
		std::vector<Common::Geometry::Pose> getPositionsToDriveOnBall(const IntelligentBall &ball) const;

		std::vector<Common::Geometry::Pose> getPositionsToGetOutOfGoalZone(const Common::Geometry::Point robotPosition) const;

		//! @todo this function might be unused
		Common::Geometry::Point getPointBehindBallInMovingDirection(const IntelligentBall &ball, double distanceToBall) const;

		bool isGoodKickPosition(const IntelligentBall &ball,const Common::Geometry::Point robotPosition, double minDistanc) const;
		bool isPositionBehindTheBall(const Common::Geometry::Point &robotPosition, const IntelligentBall &ball)const;

		Common::Geometry::Angle getOrientationToEnemyGoal() const;

	private:
		std::vector<Common::Geometry::Point> getEnemyGoalPositions(Abstraction::FieldSide fieldSide) const;

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
