#include "layer/main/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/line.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

TargetPositionFetcher::TargetPositionFetcher() :
	m_fieldside(FieldSideInvalid)
{ }

void TargetPositionFetcher::setFieldSide(FieldSide fieldside)
{
	m_fieldside = fieldside;
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

Pose TargetPositionFetcher::getOwnGoalPosition(const Ball &ball) const
{
	Pose goalPosition;
	double yPosition = ball.getPosition().getY();

	if(yPosition > 0.25)
		yPosition = 0.25;
	else if(yPosition < -0.25)
		yPosition = -0.25;

	switch (m_fieldside)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		goalPosition = Pose(Point(1.35,yPosition),Angle::getHalfRotation());
		break;
	case FieldSideLeft:
		goalPosition = Pose(Point(-1.35,yPosition),Angle());
		break;
	}

	return goalPosition;
}

Pose TargetPositionFetcher::getPenaltyPositionKicker(const Ball &ball) const
{
	Pose penaltyPosition;
	Line lineToGoal(ball.getPosition(), getEnemyGoalPosition().front());
	double percentOfLineLength = -0.05/lineToGoal.getStart().distanceTo(lineToGoal.getEnd());

	switch (m_fieldside)
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

Pose TargetPositionFetcher::mirrorPointDependentOnFieldSide(Point pointRightSide) const
{
	Pose pose;

	switch (m_fieldside)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		pose = Pose(pointRightSide,Angle::getHalfRotation());
		break;
	case FieldSideLeft:
		pose = Pose(pointRightSide*(-1),Angle());
		break;
	}

	return pose;
}