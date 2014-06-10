#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/intelligentball.h"
#include "common/geometry/pose.h"
#include "common/geometry/line.h"
#include "common/geometry/straight.h"
#include <assert.h>
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

TargetPositionFetcher::TargetPositionFetcher() :
	m_fieldSide(FieldSideInvalid)
{ }

void TargetPositionFetcher::setFieldSide(FieldSide fieldSide)
{
	m_fieldSide = fieldSide;
}

vector<Pose> TargetPositionFetcher::getStartPositionsGoalkeeper() const
{
	vector<Pose> targetPoints;

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(1.35,0)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerOneOffensive() const
{
	vector<Pose> targetPoints;

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.1,0)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerTwoOffensive() const
{
	vector<Pose> targetPoints;

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0,-0.5)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerOneDefensive() const
{
	vector<Pose> targetPoints;

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.2,0.1)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerTwoDefensive() const
{
	vector<Pose> targetPoints;

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.2,-0.1)));

	return targetPoints;
}

vector<Point> TargetPositionFetcher::getEnemyGoalPositions() const
{
	return getEnemyGoalPositions(m_fieldSide);
}

double TargetPositionFetcher::getDistanceToOwnGroundLine(const Point &position) const
{
	Point pointOnGroundLine = mirrorPointDependentOnFieldSide(m_fieldSide, Point(1.45,0));
	pointOnGroundLine.setY(position.getY());

	return pointOnGroundLine.distanceTo(position);
}

Pose TargetPositionFetcher::getTargetForGoalkeeper(const IntelligentBall &ball) const
{
	double xPositionGoalKeeperRightSide = 1.45-0.07;

	return getGoaliePositionUsingEstimatedIntersectPoint(m_fieldSide, ball, xPositionGoalKeeperRightSide);
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsPrepareKicker() const
{
	vector<Pose> preparePenaltyPosition;
	preparePenaltyPosition.push_back(Pose(Point::zero(), Angle::getHalfRotation()));

	return preparePenaltyPosition;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionKicker(const IntelligentBall &ball) const
{
	//! Penalty Goal is fixed on the left side.
	FieldSide fieldSide = FieldSideRight;

	vector<Pose> penaltyPosition;
	Line lineToGoal(ball.getPosition(), getEnemyGoalPositions(fieldSide).front());

	double percentOfLineLength = -0.11/lineToGoal.getLength();
	penaltyPosition.push_back(Pose(lineToGoal.getPointOnDirectionOfLine(percentOfLineLength), Angle::getHalfRotation()));

	return penaltyPosition;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionGoalie(const IntelligentBall &ball) const
{
	//! Penalty Goal is fixed on the left side.
	FieldSide fieldSide = FieldSideLeft;
	vector<Pose> penaltyPosition;
	penaltyPosition.push_back(getGoaliePositionUsingEstimatedIntersectPoint(fieldSide, ball, 1.25));

	return penaltyPosition;
}

Point TargetPositionFetcher::getPointBehindBallInMovingDirection(const IntelligentBall &ball, double distanceToBall) const
{
	Angle ballOrientation = ball.getRotation();
	Point pointDelta(distanceToBall, ballOrientation);
	return ball.getPosition() + pointDelta;
}

vector<Pose> TargetPositionFetcher::getAlternativeRobotPositionsAtBallHeightAggressiveMode(const IntelligentBall &ball, const Point &currentAlternativeRobotPosition) const
{
	Point enemyGoalPosition = getEnemyGoalPositions().front();
	Line alternativeRobotToEnemyGoalLine(currentAlternativeRobotPosition,enemyGoalPosition);
	double stretchFactor = -10.0/alternativeRobotToEnemyGoalLine.getLength();
	Point expandLine = alternativeRobotToEnemyGoalLine.getPointOnDirectionOfLine(stretchFactor);
	Line expandedLineRobotTarget(expandLine, enemyGoalPosition);
	Line yLineThroughBall(Point(ball.getPosition().getX(), -2.0), Point(ball.getPosition().getX(), 2.0));
	vector<Point> intersectionPoints = expandedLineRobotTarget.getIntersectPoint(yLineThroughBall);
	vector<Point> targetPoints;

	if (!intersectionPoints.empty())
	{
		Point maxPriorityPoint = intersectionPoints.front();
		targetPoints.push_back(maxPriorityPoint);
		targetPoints.push_back(maxPriorityPoint + Point(0, 0.2));
		targetPoints.push_back(maxPriorityPoint + Point(0, -0.2));
		targetPoints.push_back(maxPriorityPoint + Point(0, 0.4));
		targetPoints.push_back(maxPriorityPoint + Point(0, -0.4));
		targetPoints.push_back(maxPriorityPoint + Point(0, 0.6));
		targetPoints.push_back(maxPriorityPoint + Point(0, -0.6));
	}

	Point atHeightSimple = Point(ball.getPosition().getX(), currentAlternativeRobotPosition.getY());
	targetPoints.push_back(atHeightSimple);
	targetPoints.push_back(atHeightSimple + Point(0, 0.2));
	targetPoints.push_back(atHeightSimple + Point(0, -0.2));
	targetPoints.push_back(atHeightSimple + Point(0, 0.4));
	targetPoints.push_back(atHeightSimple + Point(0, -0.4));
	targetPoints.push_back(atHeightSimple + Point(0, 0.6));
	targetPoints.push_back(atHeightSimple + Point(0, -0.6));

	vector<Pose> results;
	results.reserve(targetPoints.size());
	Angle orientation = getOrientationToEnemyGoal();
	for (vector<Point>::const_iterator i = targetPoints.begin(); i != targetPoints.end(); ++i)
	{
		Point currentPoint = *i;
		double x = currentPoint.getX();
		x = min(x, 1.0);
		x = max(x, -1.0);
		currentPoint.setX(x);
		results.push_back(Pose(currentPoint, orientation));
	}

	return results;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsUnusedPlayerOne() const
{
	vector<Pose> positions;
	positions.reserve(3);

	positions.push_back(Pose(Point(1.1, 0.5), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.15, 0.6), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.05, 0.5), Angle::getHalfRotation()));

	return positions;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsUnusedPlayerTwo() const
{
	vector<Pose> positions;
	positions.reserve(3);

	positions.push_back(Pose(Point(1.1, 0.2), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.15, 0.1), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.05, 0.2), Angle::getHalfRotation()));

	return positions;
}

bool TargetPositionFetcher::isGoodKickPosition(const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const Point robotPosition, const Angle &spanAngle, double minDistance) const
{
	Point ballPosition = ball.getPosition();
	Point goalPosition = getEnemyGoalPositions().front();
	Angle angleGoalBall(goalPosition,ballPosition);
	Angle angleBallRobot(ballPosition,robotPosition);
	Angle deltaAngle = angleGoalBall-angleBallRobot;
	double distanceRobotBall = ballPosition.distanceTo(robotPosition);
	return ((fabs(deltaAngle.getValueBetweenMinusPiAndPi()) < spanAngle.getValueBetweenMinusPiAndPi()) && (distanceRobotBall < minDistance));
}

bool TargetPositionFetcher::isPositionBehindTheBall(const Point &robotPosition, const IntelligentBall &ball) const
{
	Point ballPosition = ball.getPosition();
	Angle angleCircularSector = Angle::getQuarterRotation();
	Angle straight1Direction;
	Angle straight2Direction;

	if(m_fieldSide == FieldSideRight)
	{
		straight1Direction = (angleCircularSector * 0.5);
		straight2Direction = Angle::getHalfRotation() - (angleCircularSector * 0.5);
	}
	else
	{
		straight1Direction = Angle::getHalfRotation() + (angleCircularSector * 0.5);
		straight2Direction = angleCircularSector * (-0.5);
	}

	Straight straight1(ballPosition, straight1Direction);
	Straight straight2(ballPosition, straight2Direction);

	return straight1.isTargetPointRightOfLine(robotPosition) && straight2.isTargetPointRightOfLine(robotPosition);
}

vector<Pose> TargetPositionFetcher::getPositionsToDriveOnBall(const IntelligentBall &ball) const
{
	Angle orientation = getOrientationToEnemyGoal();
	Point ballPosition = ball.getPosition();
	vector<Pose> result;
	result.push_back(Pose(ballPosition, orientation));
	result.push_back(Pose(ballPosition + Point(0, 0.05), orientation));
	result.push_back(Pose(ballPosition + Point(0, -0.05), orientation));
	result.push_back(Pose(ballPosition + Point(0.05, 0), orientation));
	result.push_back(Pose(ballPosition + Point(-0.05, 0), orientation));
	return result;
}

vector<Point> TargetPositionFetcher::getEnemyGoalPositions(FieldSide fieldSide) const
{
	vector<Point> goalposition;
	goalposition.reserve(3);

	goalposition.push_back(mirrorPointDependentOnFieldSide(fieldSide, Point(-1.45,0)).getPosition());
	goalposition.push_back(mirrorPointDependentOnFieldSide(fieldSide, Point(-1.45,-0.2)).getPosition());
	goalposition.push_back(mirrorPointDependentOnFieldSide(fieldSide, Point(-1.45,0.2)).getPosition());

	return goalposition;
}

Pose TargetPositionFetcher::mirrorPointDependentOnFieldSide(FieldSide fieldSide, Point pointFieldSideRight) const
{
	Pose pose;

	switch (fieldSide)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		pose = Pose(pointFieldSideRight,Angle::getHalfRotation());
		break;
	case FieldSideLeft:
		pose = Pose(pointFieldSideRight*(-1),Angle());
		break;
	}

	return pose;
}

Pose TargetPositionFetcher::getGoaliePositionUsingEstimatedIntersectPoint(FieldSide fieldSide, const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const
{
	if (ball.isMoving())
	{
		if(ball.getMovingDirection() == fieldSide && ball.getCurrentFieldSide() == fieldSide)
		{
			double xPositionGoalKeeperRightSideModified = xPositionGoalKeeperRightSide;
			switch (fieldSide)
			{
			case FieldSideInvalid:
				assert(false);
			case FieldSideRight:
				break;
			case FieldSideLeft:
				xPositionGoalKeeperRightSideModified *= -1;
				break;
			}

			Straight ballMovingStraight(ball.getPosition(),ball.getRotation());
			Line goalKeeperMovingLine(Point(xPositionGoalKeeperRightSideModified,-0.2),Point(xPositionGoalKeeperRightSideModified,0.2));

			if (!ballMovingStraight.getIntersectPoint(goalKeeperMovingLine).empty())
				return Pose(ballMovingStraight.getIntersectPoint(goalKeeperMovingLine).front(),Angle::getQuarterRotation());
		}
	}

	return getGoaliePositionUsingIntersectWithGoalCenter(fieldSide, ball, xPositionGoalKeeperRightSide);
}

Pose TargetPositionFetcher::getGoaliePositionUsingIntersectWithGoalCenter(FieldSide fieldSide, const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const
{
	double xPositionBehindGoalCenter = 1.5;

	switch (fieldSide)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		break;
	case FieldSideLeft:
		xPositionBehindGoalCenter *= -1;
		xPositionGoalKeeperRightSide *= -1;
		break;
	}

	Line ballToGoalCenterLine(ball.getPosition(),Point(xPositionBehindGoalCenter,0));
	Line goalKeeperMovingLine(Point(xPositionGoalKeeperRightSide,-0.2),Point(xPositionGoalKeeperRightSide,0.2));

	if(ballToGoalCenterLine.getIntersectPoint(goalKeeperMovingLine).empty())
		return getGoaliePositionUsingYCoordinateFollowing(ball,xPositionGoalKeeperRightSide);

	return Pose(ballToGoalCenterLine.getIntersectPoint(goalKeeperMovingLine).front(),Angle::getQuarterRotation());

}

Pose TargetPositionFetcher::getGoaliePositionUsingYCoordinateFollowing(const IntelligentBall &ball, double xPositionGoalKeeper) const
{
	double yBall = ball.getPosition().getY();
	if(fabs(yBall) < 0.2)
		return Pose(Point(xPositionGoalKeeper,yBall),Angle::getQuarterRotation());

	if(yBall > 0.2)
		return Pose(Point(xPositionGoalKeeper,0.2),Angle::getQuarterRotation());
	else
		return Pose(Point(xPositionGoalKeeper,-0.2),Angle::getQuarterRotation());
}

Angle TargetPositionFetcher::getOrientationToEnemyGoal() const
{
	Angle ballOrientation;
	if (m_fieldSide == FieldSideLeft)
		ballOrientation = Angle::getHalfRotation();

	return ballOrientation;
}

vector<Pose> TargetPositionFetcher::getTargetBehindBall(const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, double distanceToBall) const
{
	vector<Pose> targetPoint;
	Angle ballOrientation = getOrientationToEnemyGoal();
	Point resultPoint = ball.getPosition() + Point(distanceToBall, ballOrientation);
	targetPoint.push_back(Pose(resultPoint, ballOrientation + Angle::getHalfRotation()));

	return targetPoint;

}
