#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include "layer/autonomous/intelligentball.h"
#include "common/geometry/line.h"
#include <assert.h>

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

Pose TargetPositionFetcher::getStartPositionGoalkeeper() const
{
	return mirrorPointDependentOnFieldSide(Point(1.35,0));
}

Pose TargetPositionFetcher::getStartPositionPlayerOneOffensive() const
{
	return mirrorPointDependentOnFieldSide(Point(0.1,0));
}

Pose TargetPositionFetcher::getStartPositionPlayerTwoOffensive() const
{
	return mirrorPointDependentOnFieldSide(Point(0,-0.5));
}

Pose TargetPositionFetcher::getStartPositionPlayerOneDefensive() const
{
	return mirrorPointDependentOnFieldSide(Point(0.2,0.1));
}

Pose TargetPositionFetcher::getStartPositionPlayerTwoDefensive() const
{
	return mirrorPointDependentOnFieldSide(Point(0.2,-0.1));
}

std::vector<Point> TargetPositionFetcher::getEnemyGoalPosition() const
{
	vector<Point> goalposition;
	goalposition.reserve(3);

	goalposition.push_back(mirrorPointDependentOnFieldSide(Point(1.45,0)).getPosition());
	goalposition.push_back(mirrorPointDependentOnFieldSide(Point(1.45,-0.2)).getPosition());
	goalposition.push_back(mirrorPointDependentOnFieldSide(Point(1.45,0.2)).getPosition());

	return goalposition;
}

Pose TargetPositionFetcher::getOwnGoalPosition(const IntelligentBall &ball) const
{
	double xPositionGoalKeeperRightSide = 1.45-0.07;
	Angle angle;

	if (ball.isMoving() && ball.getMovingDirection() == m_fieldSide && ball.getCurrentFieldSide() == m_fieldSide)
	{
		switch (m_fieldSide)
		{
		case FieldSideInvalid:
			assert(false);
		case FieldSideRight:
			angle = Angle::getHalfRotation();
			break;
		case FieldSideLeft:
			xPositionGoalKeeperRightSide *= -1;
			break;
		}

		Line ballMovingLine(ball.getPosition(),ball.getRotation(),4);
		Line goalKeeperMovingLine(Point(xPositionGoalKeeperRightSide,-0.2),Point(xPositionGoalKeeperRightSide,0.2));

		if (!ballMovingLine.getIntersectPoint(goalKeeperMovingLine).empty())
			return Pose(ballMovingLine.getIntersectPoint(goalKeeperMovingLine).front(),angle);
	}

	return getGoaliePositionUsingStandardTactic(ball, xPositionGoalKeeperRightSide);
}

Pose TargetPositionFetcher::getPenaltyPositionKicker(const IntelligentBall &ball) const
{
	Pose penaltyPosition;
	Line lineToGoal(ball.getPosition(), getEnemyGoalPosition().front());
	double percentOfLineLength = -0.05/lineToGoal.getStart().distanceTo(lineToGoal.getEnd());

	switch (m_fieldSide)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		penaltyPosition = Pose(lineToGoal.getPointOnDirectionOfLine(percentOfLineLength),Angle());
		break;
	case FieldSideLeft:
		penaltyPosition = Pose(lineToGoal.getPointOnDirectionOfLine(percentOfLineLength),Angle::getHalfRotation());
		break;
	}

	return penaltyPosition;
}

Pose TargetPositionFetcher::getPenaltyPositionGoalie(const IntelligentBall &ball) const
{
	return getGoaliePositionUsingStandardTactic(ball, 1.25);
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsUnusedPlayerOne() const
{
	vector<Pose> positions;
	positions.reserve(3);

	positions.push_back(mirrorPointDependentOnFieldSide(Point(-1.25, 0.7)));
	positions.push_back(mirrorPointDependentOnFieldSide(Point(-1.15, 0.7)));
	positions.push_back(mirrorPointDependentOnFieldSide(Point(-1.25, 0.6)));

	return positions;
}

vector<Pose> TargetPositionFetcher::getPenaltyPositionsUnusedPlayerTwo() const
{
	vector<Pose> positions;
	positions.reserve(3);

	positions.push_back(mirrorPointDependentOnFieldSide(Point(-1.25, -0.7)));
	positions.push_back(mirrorPointDependentOnFieldSide(Point(-1.15, -0.7)));
	positions.push_back(mirrorPointDependentOnFieldSide(Point(-1.25, -0.6)));

	return positions;
}

Pose TargetPositionFetcher::mirrorPointDependentOnFieldSide(Point pointFieldSideRight) const
{
	Pose pose;

	switch (m_fieldSide)
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

Pose TargetPositionFetcher::getGoaliePositionUsingStandardTactic(const IntelligentBall &ball, double xPositionGoalKeeperRightSide) const
{
	double xPositionBehindGoalCenter = 1.5;
	Angle angle;

	switch (m_fieldSide)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		angle = Angle::getHalfRotation();
		break;
	case FieldSideLeft:
		xPositionBehindGoalCenter *= -1;
		xPositionGoalKeeperRightSide *= -1;
		break;
	}

	Line ballToGoalCenterLine(ball.getPosition(),Point(xPositionBehindGoalCenter,0));
	Line goalKeeperMovingLine(Point(xPositionGoalKeeperRightSide,-0.2),Point(xPositionGoalKeeperRightSide,0.2));

	return Pose(ballToGoalCenterLine.getIntersectPoint(goalKeeperMovingLine).front(),angle);
}
