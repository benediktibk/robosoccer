#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/fieldpositioncheckerfieldplayer.h"
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
	targetPoints.reserve(3);

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(1.35,0)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(1.35,0.1)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(1.35,-0.1)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerOneOffensive() const
{
	vector<Pose> targetPoints;
	targetPoints.reserve(3);

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.1,0)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.1,0.15)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.1,-0.15)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerTwoOffensive() const
{
	vector<Pose> targetPoints;
	targetPoints.reserve(4);

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0,-0.5)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0,0.5)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.1,-0.5)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.1,0.5)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerOneDefensive() const
{
	vector<Pose> targetPoints;
	targetPoints.reserve(4);

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.2,0)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.3,0)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.2,0.1)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.5,0.2)));

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getStartPositionsPlayerTwoDefensive() const
{
	vector<Pose> targetPoints;
	targetPoints.reserve(3);

	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.2,-0.1)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.5,-0.2)));
	targetPoints.push_back(mirrorPointDependentOnFieldSide(m_fieldSide, Point(0.5,0.2)));

	return targetPoints;
}

vector<Point> TargetPositionFetcher::getEnemyGoalPositions() const
{
	return getEnemyGoalPositions(m_fieldSide);
}

vector<Point> TargetPositionFetcher::getOwnGoalPositions() const
{
	FieldSide fieldSide = m_fieldSide == FieldSideLeft ? FieldSideRight : FieldSideLeft;
	return getEnemyGoalPositions(fieldSide);
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
	preparePenaltyPosition.reserve(3);

	preparePenaltyPosition.push_back(Pose(Point::zero(), Angle::getHalfRotation()));
	preparePenaltyPosition.push_back(Pose(Point(0,0.2), Angle::getHalfRotation()));
	preparePenaltyPosition.push_back(Pose(Point(0,-0.2), Angle::getHalfRotation()));

	return preparePenaltyPosition;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionKicker(const IntelligentBall &ball) const
{
	//! Penalty Goal is fixed on the left side.
	FieldSide fieldSide = FieldSideRight;

	vector<Pose> penaltyPosition;
	penaltyPosition.reserve(1);
	Line lineToGoal(ball.getPosition(), getEnemyGoalPositions(fieldSide).front());

	//! @todo maybe this value has to be increased/improved
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

vector<Pose> TargetPositionFetcher::getAlternativeRobotPositionsBehindBallAggressiveMode(const IntelligentBall &ball) const
{
	double maxX = 1.1;
	double maxY = 0.6;
	double ballX = ball.getPosition().getX();
	double ballY = ball.getPosition().getY();

	if(m_fieldSide == FieldSideLeft)
		ballX += -0.5;
	else
		ballX += 0.5;

	if(ballX > maxX)
		ballX = maxX;
	else if(ballX < -maxX)
		ballX = -maxX;

	if(ballY > maxY)
		ballY = maxY;
	else if(ballY < -maxY)
		ballY = -maxY;

	vector<Pose> targets;
	targets.reserve(5);
	Angle orientation = getOrientationToEnemyGoal();
	Pose maxPriorityPoint = Pose(Point(ballX, ballY),orientation);

	targets.push_back(maxPriorityPoint);
	targets.push_back(maxPriorityPoint + Pose(Point(0, 0.1), Angle()));
	targets.push_back(maxPriorityPoint + Pose(Point(0, -0.1), Angle()));
	targets.push_back(maxPriorityPoint + Pose(Point(0.1, 0), Angle()));
	targets.push_back(maxPriorityPoint + Pose(Point(-0.1, 0), Angle()));

	return targets;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsUnusedPlayerOne() const
{
	vector<Pose> positions;
	positions.reserve(8);

	positions.push_back(Pose(Point(0.7, 0.5), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(0.7, 0.7), Angle::getHalfRotation()));

	positions.push_back(Pose(Point(0.9, 0.5), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(0.9, 0.7), Angle::getHalfRotation()));

	positions.push_back(Pose(Point(1.1, 0.5), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.1, 0.7), Angle::getHalfRotation()));

	positions.push_back(Pose(Point(1.3, 0.5), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.3, 0.7), Angle::getHalfRotation()));

	return positions;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsUnusedPlayerTwo() const
{
	vector<Pose> positions;
	positions.reserve(8);

	positions.push_back(Pose(Point(0.7, 0.2), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(0.7, 0.0), Angle::getHalfRotation()));

	positions.push_back(Pose(Point(0.9, 0.2), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(0.9, 0.0), Angle::getHalfRotation()));

	positions.push_back(Pose(Point(1.1, 0.2), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.1, 0.0), Angle::getHalfRotation()));

	positions.push_back(Pose(Point(1.3, 0.2), Angle::getHalfRotation()));
	positions.push_back(Pose(Point(1.3, 0.0), Angle::getHalfRotation()));

	return positions;
}

bool TargetPositionFetcher::isGoodKickPosition(const IntelligentBall &ball, const Point robotPosition, double minDistance) const
{
	Point ballPosition = ball.getPosition();
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	if (fieldPositionChecker.isPointInsideGoalZone(ballPosition))
		return false;

	const double fieldWidth = 1.7;
	const Angle maxAngle(Angle::convertFromDegreeToRadiant(70));
	const Angle minAngle(Angle::convertFromDegreeToRadiant(25));
	double m = (maxAngle-minAngle).getValueBetweenZeroAndTwoPi()/fieldWidth*2;
	Angle spanAngle(m*fabs(robotPosition.getY())+minAngle.getValueBetweenZeroAndTwoPi());

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
	result.reserve(5);

	result.push_back(Pose(ballPosition, orientation));
	result.push_back(Pose(ballPosition + Point(0, 0.05), orientation));
	result.push_back(Pose(ballPosition + Point(0, -0.05), orientation));
	result.push_back(Pose(ballPosition + Point(0.05, 0), orientation));
	result.push_back(Pose(ballPosition + Point(-0.05, 0), orientation));

	return result;
}

vector<Pose> TargetPositionFetcher::getPositionsToGetOutOfGoalZone(const Point robotPosition) const
{
	vector<Pose> result;
	result.reserve(3);
	double robotY = robotPosition.getY();

	switch (m_fieldSide)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		result.push_back(Pose(Point(-0.55, robotY), Angle::getHalfRotation()));
		result.push_back(Pose(Point(-0.40, robotY), Angle::getHalfRotation()));
		result.push_back(Pose(Point(-0.70, robotY), Angle::getHalfRotation()));
		break;
	case FieldSideLeft:
		result.push_back(Pose(Point(0.55, robotY), Angle()));
		result.push_back(Pose(Point(0.40, robotY), Angle()));
		result.push_back(Pose(Point(0.70, robotY), Angle()));
		break;
	}

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

vector<Pose> TargetPositionFetcher::getTargetsBehindBall(const IntelligentBall &ball) const
{
	vector<Pose> targetPoints;
	targetPoints.reserve(4);
	static double distanceToBall = 0.2;
	Point ballPosition = ball.getPosition();
	Line enemyGoalToBall(getEnemyGoalPositions().front(),ballPosition);
	Point maxProrityPoint = enemyGoalToBall.getPointOnDirectionOfLine((enemyGoalToBall.getLength()+distanceToBall)/enemyGoalToBall.getLength());
	targetPoints.push_back(Pose(maxProrityPoint, Angle(enemyGoalToBall.getStart(),enemyGoalToBall.getEnd())));

	Angle ballOrientation = getOrientationToEnemyGoal();
	Point secondPriorityPoint = ball.getPosition() + Point(distanceToBall, ballOrientation);
	targetPoints.push_back(Pose(secondPriorityPoint, ballOrientation + Angle::getHalfRotation()));
	Point targetLeftViewFromGoalie1;
	Point targetLeftViewFromGoalie2;
	Point targetRightViewFromGoalie1;
	Point targetRightViewFromGoalie2;
	if (m_fieldSide == FieldSideLeft)
	{
		targetLeftViewFromGoalie1 = ballPosition - Point(0,distanceToBall);
		targetLeftViewFromGoalie2 = ballPosition - Point(0,distanceToBall/2.0);
		targetRightViewFromGoalie1 = ballPosition + Point(0,distanceToBall);
		targetRightViewFromGoalie2 = ballPosition + Point(0,distanceToBall/2.0);
	}
	else
	{
		targetLeftViewFromGoalie1 = ballPosition + Point(0,distanceToBall);
		targetLeftViewFromGoalie2 = ballPosition + Point(0,distanceToBall/2.0);
		targetRightViewFromGoalie1 = ballPosition - Point(0,distanceToBall);
		targetRightViewFromGoalie2 = ballPosition - Point(0,distanceToBall/2.0);
	}
	Angle yAngle = Angle::getQuarterRotation();

	if (ballPosition.getY() < 0)
	{
		if (ballPosition.getX() < 0)
		{
			targetPoints.push_back(Pose(targetRightViewFromGoalie1, yAngle));
			targetPoints.push_back(Pose(targetRightViewFromGoalie2, yAngle));
		}
		else
		{
			targetPoints.push_back(Pose(targetLeftViewFromGoalie1, yAngle));
			targetPoints.push_back(Pose(targetLeftViewFromGoalie2, yAngle));
		}
	}
	else
	{
		if (ballPosition.getX() < 0)
		{
			targetPoints.push_back(Pose(targetLeftViewFromGoalie1, yAngle));
			targetPoints.push_back(Pose(targetLeftViewFromGoalie2, yAngle));
		}
		else
		{
			targetPoints.push_back(Pose(targetRightViewFromGoalie1, yAngle));
			targetPoints.push_back(Pose(targetRightViewFromGoalie2, yAngle));
		}
	}

	return targetPoints;
}

vector<Pose> TargetPositionFetcher::getTargetsBehindBallAlternativeRobot(const IntelligentBall &ball) const
{
	vector<Pose> targetPoints;
	targetPoints.reserve(3);
	Point ballPosition = ball.getPosition();
	Line ballToPointIfFrontOfGoal(ballPosition, Point(1.2,0));

	Point maxProrityPoint = ballToPointIfFrontOfGoal.getPointOnDirectionOfLine(0.5);
	targetPoints.push_back(Pose(maxProrityPoint, Angle(ballToPointIfFrontOfGoal.getStart(),ballToPointIfFrontOfGoal.getEnd())));

	Point secondMaxProrityPoint = ballToPointIfFrontOfGoal.getPointOnDirectionOfLine(0.7);
	targetPoints.push_back(Pose(secondMaxProrityPoint, Angle(ballToPointIfFrontOfGoal.getStart(),ballToPointIfFrontOfGoal.getEnd())));

	Point thirdMaxProrityPoint = ballToPointIfFrontOfGoal.getPointOnDirectionOfLine(0.8);
	targetPoints.push_back(Pose(thirdMaxProrityPoint, Angle(ballToPointIfFrontOfGoal.getStart(),ballToPointIfFrontOfGoal.getEnd())));

	return targetPoints;
}
