#include "common/geometry/line.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/compare.h"
#include <math.h>

using namespace RoboSoccer::Common::Geometry;
using namespace std;

Line::Line(const Point &start, const Point &end) :
	m_start(start),
	m_end(end)
{ }

Line::Line(const Point &start, const Angle &angle, double distance) :
	m_start(start),
	m_end(start + Point(distance, angle))
{ }

vector<Point> Line::getIntersectPoints(const Circle &circle) const
{
	Point start(m_start - circle.getCenter());
	Point end(m_end - circle.getCenter());
	vector<Point> intersectPoints;
	intersectPoints.reserve(2);
	Angle angleForVerticalLines;
	double gradient;
	Other::Compare compare(0.001);

	if(compare.isFuzzyEqual(end.getX(), start.getX()))
	{
		gradient = 0;
		angleForVerticalLines = Angle::getThreeQuarterRotation();
		start.rotate(angleForVerticalLines);
		end.rotate(angleForVerticalLines);
	}
	else
	{
		Point startToEndDifference = end - start;
		gradient = startToEndDifference.getY()/startToEndDifference.getX();
	}

	double yAxisIntercept = start.getY() - gradient*start.getX();
	double radius = circle.getDiameter()/2;
	double linearComponent = 2*gradient*yAxisIntercept;
	double squareComponent = gradient*gradient + 1;
	double discriminant = linearComponent*linearComponent - 4*squareComponent*(yAxisIntercept*yAxisIntercept - radius*radius);

	if (discriminant < 0)
		return intersectPoints;
	else
	{
		if (discriminant == 0)
		{
			double resultX = -linearComponent/(2*squareComponent);
			Point result(resultX, gradient*resultX + yAxisIntercept);
			if(angleForVerticalLines.getValueBetweenZeroAndTwoPi() != 0)
				result.rotate(Angle::getQuarterRotation());
			if((compare.isFuzzyGreater(resultX, start.getX()) && compare.isFuzzySmaller(resultX, end.getX())) ||
				(compare.isFuzzySmaller(resultX, start.getX()) && compare.isFuzzyGreater(resultX, end.getX())))
			{
				result = result	+ circle.getCenter();
				intersectPoints.push_back(result);
			}
		}
		else
		{
			double resultX1 = (-linearComponent + sqrt(discriminant)) / (2*squareComponent);
			double resultX2 = (-linearComponent - sqrt(discriminant)) / (2*squareComponent);
			Point resultPlus(resultX1, gradient*resultX1 + yAxisIntercept);
			Point resultMinus(resultX2, gradient*resultX2 + yAxisIntercept);
			if(angleForVerticalLines.getValueBetweenZeroAndTwoPi() != 0)
			{
				resultPlus.rotate(Angle::getQuarterRotation());
				resultMinus.rotate(Angle::getQuarterRotation());
			}
			if((compare.isFuzzyGreater(resultX1, start.getX()) && compare.isFuzzySmaller(resultX1, end.getX())) ||
				(compare.isFuzzySmaller(resultX1, start.getX()) && compare.isFuzzyGreater(resultX1, end.getX())) ||
				(compare.isFuzzyGreater(resultX2, start.getX()) && compare.isFuzzySmaller(resultX2, end.getX())) ||
				(compare.isFuzzySmaller(resultX2, start.getX()) && compare.isFuzzyGreater(resultX2, end.getX())))
			{
				resultPlus = resultPlus + circle.getCenter();
				resultMinus = resultMinus + circle.getCenter();
				intersectPoints.push_back(resultPlus);
				intersectPoints.push_back(resultMinus);
			}
		}
	}
	return intersectPoints;
}

vector<Point> Line::getIntersectPoint(const Line &line) const
{
	vector<Point> intersectPoint;
	intersectPoint.reserve(1);
	Point vectorOne = m_end - m_start;
	Point vectorTwo = line.getEnd() - line.getStart();
	double determinantSolutionMatrix = vectorTwo.getX()*(-vectorOne.getY()) + vectorTwo.getY()*vectorOne.getX();

	if (determinantSolutionMatrix != 0)
	{
		double percentOfLineOne = (-vectorTwo.getY()*(m_start.getX()-line.getStart().getX()) +
								   vectorTwo.getX()*(m_start.getY()-line.getStart().getY())) / determinantSolutionMatrix;

		double percentOfLineTwo = (-vectorOne.getY()*(m_start.getX()-line.getStart().getX()) +
								   vectorOne.getX()*(m_start.getY()-line.getStart().getY())) / determinantSolutionMatrix;

		if (percentOfLineOne >= 0 && percentOfLineOne <= 1 && percentOfLineTwo >= 0 && percentOfLineTwo <= 1)
			intersectPoint.push_back(m_start + vectorOne*percentOfLineOne);
	}

	return intersectPoint;
}

Point Line::getPerpendicularPoint(Point point) const
{
	Angle angleBetweenPoints(m_start, m_end);

	point = point - m_start;
	point.rotate(Angle::getFullRotation() - angleBetweenPoints);

	Point perpendicularPoint(point.getX(),0);
	perpendicularPoint.rotate(angleBetweenPoints);
	perpendicularPoint = perpendicularPoint + m_start;

	return perpendicularPoint;
}

Point Line::getPointOnDirectionOfLine(double percentOfLenghtOfLine) const
{
	Point direction(m_end - m_start);

	return m_start + direction * percentOfLenghtOfLine;
}

bool Line::isTargetPointRightOfLine(const Point &target) const
{
	Angle angleBetweenPoints(m_start, m_end);
	Point point(target);

	point = point - m_start;
	point.rotate(Angle::getFullRotation() - angleBetweenPoints);

	return point.getY() < 0;
}

bool Line::isOnePointLeftAndOneRightOfLine(const Point &one, const Point &two) const
{
	unsigned int pointsLeft = 0;
	unsigned int pointsRight = 0;

	if (isTargetPointRightOfLine(one))
		++pointsRight;
	else
		++pointsLeft;

	if (isTargetPointRightOfLine(two))
		++pointsRight;
	else
		++pointsLeft;

	return pointsLeft == 1 && pointsRight == 1;
}

void Line::shiftParallel(const Point &point)
{
	Point direction(m_end - m_start);
	m_start = point;
	m_end = m_start + direction;
}

Point Line::getStart() const
{
	return m_start;
}

Point Line::getEnd() const
{
	return m_end;
}
