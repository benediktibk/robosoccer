#ifndef ROBOSOCCER_COMMON_GEOMETRY_POINT_H
#define ROBOSOCCER_COMMON_GEOMETRY_POINT_H

#include <ostream>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
class Angle;

class Point
{
public:
	Point();
	Point(double x, double y);
	Point(double distance, const Angle &angle);

	void setX(double value);
	double getX() const;
	void setY(double value);
	double getY() const;
	void rotate(const Angle &angle);

	bool operator==(const Point &point) const;
	Point operator*(double value) const;
	Point operator/(double value) const;
	Point operator+(const Point &point) const;
	Point operator-(const Point &point) const;
	void operator*=(double value);
	double distanceTo(const Point &point) const;

public:
	static const Point& zero();

private:
	double m_x;
	double m_y;

private:
	static const Point m_zero;
};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Common::Geometry::Point &point);

#endif
