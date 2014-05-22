#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"
#include "common/geometry/line.h"
#include "layer/autonomous/obstaclefetcher.h"
#include <assert.h>
#include <math.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

IntelligentBallImpl::IntelligentBallImpl(const Ball &ball) :
	m_ball(ball)
{ }

Angle IntelligentBallImpl::getRotation() const
{
	return m_ball.getRotation();
}

vector<Circle> IntelligentBallImpl::getObstacles() const
{
	vector<Circle> result;
	result.push_back(getObstacle());
	return result;
}

Circle IntelligentBallImpl::getObstacle() const
{
	return m_ball.getObstacle();
}

double IntelligentBallImpl::getVelocity() const
{
	return m_ball.getVelocity();
}

bool IntelligentBallImpl::isMoving() const
{
	return(m_ball.getVelocity() > 0.2);
}

FieldSide IntelligentBallImpl::getMovingDirection() const
{
	assert(isMoving());

	double angle = m_ball.getRotation().getValueBetweenMinusPiAndPi();
	double piHalf = Angle::getQuarterRotation().getValueBetweenMinusPiAndPi();

	if (fabs(angle) < piHalf)
		return FieldSideRight;
	else
		return FieldSideLeft;
}

FieldSide IntelligentBallImpl::getCurrentFieldSide() const
{
	if (m_ball.getPosition().getX() > 0)
		return FieldSideRight;
	else
		return FieldSideLeft;
}

Point IntelligentBallImpl::getPosition() const
{
	return m_ball.getPosition();
}

double IntelligentBallImpl::getShootingLineCoveragePercent(ObstacleFetcher &obstacles, Point &target) const
{
	int coverageArray[100] = {0};
	vector<Circle> obstaclesWithoutBall = obstacles.getAllObstaclesButMe(*this);
	Line ballToTargetLine(getPosition(), target);
	double ballRadius = getObstacle().getDiameter()/2.0;

	for (vector<Circle>::const_iterator i = obstaclesWithoutBall.begin(); i != obstaclesWithoutBall.end(); ++i)
	{
		Circle const &currentObstacle = *i;
		Point obstaclePosition = currentObstacle.getCenter();
		Point perpendicularPoint = ballToTargetLine.getPerpendicularPoint(obstaclePosition);
		double distanceRobotEdgeToLine = obstaclePosition.distanceTo(perpendicularPoint);
		distanceRobotEdgeToLine -= currentObstacle.getDiameter()/2.0;
		int startIteration = 0;
		int endIteration = 0;
		bool isRight = (ballToTargetLine.isTargetPointRightOfLine(obstaclePosition));

		if(distanceRobotEdgeToLine > 0 && distanceRobotEdgeToLine <= ballRadius)
		{
			int percentageFree = static_cast<int>((distanceRobotEdgeToLine)/(ballRadius*2.0)*100.0 + 0.5);
			assert(percentageFree >= 0 && percentageFree <= 50);
			if(isRight)
			{
				startIteration = 49 + percentageFree;
				endIteration = 100;
			}
			else
			{
				startIteration = 0;
				endIteration = 50 - percentageFree;
			}
		}
		if(distanceRobotEdgeToLine > -ballRadius && distanceRobotEdgeToLine <= 0)
		{
			int percentageFree = static_cast<int>(ballRadius+distanceRobotEdgeToLine)/(2.0*ballRadius)*100 +0.5;
			assert(percentageFree >= 0 && percentageFree <= 50);
			if(isRight)
			{
				startIteration = percentageFree;
				endIteration = 100;
			}else
			{
				startIteration = 0;
				endIteration = 49 + percentageFree;
			}
		}
		if(distanceRobotEdgeToLine <= -ballRadius)
		{
			startIteration = 0;
			endIteration = 100;
		}
		assert(startIteration >= 0 && startIteration <= 100);
		assert(endIteration >= 0 && endIteration <= 100);
		for (int i = startIteration; i < endIteration; ++i)
			coverageArray[i] = 1;

	}
	int sumOfElements = 0;

	for (int i = 0 ; i < 100; ++i)
	{
		sumOfElements += coverageArray[i];
	}

	return static_cast<double>(sumOfElements);
}
