#include "common/geometry/orientedposition.h"
#include "common/geometry/compare.h"
#include <math.h>
#include <sstream>

using namespace RoboSoccer::Common::Geometry;
using namespace std;

OrientedPosition::OrientedPosition()
{ }

OrientedPosition::OrientedPosition(const Point &point, const Angle &orientation):
	m_position(point),
	m_orientation(orientation)
{ }

void OrientedPosition::setOrientation(const Angle &orientation)
{
	m_orientation = orientation;
}

const Angle& OrientedPosition::getOrientation() const
{
	return m_orientation;
}

void OrientedPosition::setPosition(const Point &position)
{
	m_position = position;
}

const Point &OrientedPosition::getPosition() const
{
	return m_position;
}

bool OrientedPosition::operator ==(const OrientedPosition &position) const
{
	Compare compare(0.00001);
	return compare.isFuzzyEqual(*this, position);
}

OrientedPosition OrientedPosition::operator*(double value) const
{
	return OrientedPosition(m_position*value, m_orientation);
}

OrientedPosition OrientedPosition::operator/(double value) const
{
	return OrientedPosition(m_position/value, m_orientation);
}

OrientedPosition OrientedPosition::operator+(const OrientedPosition &point) const
{
	return OrientedPosition(m_position + point.getPosition(), 0);
}

OrientedPosition OrientedPosition::operator-(const OrientedPosition &point) const
{
	return OrientedPosition(m_position - point.getPosition(), 0);
}

void OrientedPosition::operator *=(double value)
{
	m_position *= value;
}

OrientedPosition::operator Point() const
{
	return m_position;
}

double OrientedPosition::distanceTo(const OrientedPosition &point) const
{
	return m_position.distanceTo(point.getPosition());
}

void OrientedPosition::read(const string &data)
{
	size_t openingBracket = data.find_first_of('(');
	size_t firstComma = data.find_first_of(',', openingBracket);
	size_t secondComma = data.find_first_of(',', firstComma + 1);
	size_t closingBracket = data.find_first_of(')', secondComma);
	string xString(data.substr(openingBracket + 1, firstComma - openingBracket - 1));
	string yString(data.substr(firstComma + 2, secondComma - firstComma - 2));
	string angleString(data.substr(secondComma + 2, closingBracket - secondComma - 2));
	stringstream xStringStream(xString);
	stringstream yStringStream(yString);
	stringstream angleStringStream(angleString);
	double x = 0;
	double y = 0;
	double angle = 0;
	xStringStream >> x;
	yStringStream >> y;
	angleStringStream >> angle;
	m_position = Point(x, y);
	m_orientation = Angle(angle);
}

Angle OrientedPosition::getRelativeOrientationTo(const Point &point) const
{
	return Angle(m_position, point) - m_orientation;
}

ostream &operator<<(ostream &stream, const OrientedPosition &point)
{
	const Point &position = point.getPosition();
	stream << "(" << position.getX() << ", " << position.getY() << ", " << point.getOrientation() << ")";
	return stream;
}
