#ifndef ROBOSOCCER_COMMON_GEOMETRY_ORIENTEDPOSITION_H
#define ROBOSOCCER_COMMON_GEOMETRY_ORIENTEDPOSITION_H

#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include <ostream>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class OrientedPosition
	{
	public:
		OrientedPosition();
		OrientedPosition(const Point &point, const Angle &orientation);

		void setOrientation(const Angle &orientation);
		const Angle& getOrientation() const;
		void setPosition(const Point &position);
		const Point& getPosition() const;
		double distanceTo(const OrientedPosition &point) const;
		void read(const std::string &data);
		Angle getRelativeOrientationTo(const Point &point) const;

		bool operator ==(const OrientedPosition &position) const;
		OrientedPosition operator*(double value) const;
		OrientedPosition operator/(double value) const;
		OrientedPosition operator+(const OrientedPosition &point) const;
		OrientedPosition operator-(const OrientedPosition &point) const;
		void operator*=(double value);
		operator Point() const;

	private:
		Point m_position;
		Angle m_orientation;
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Common::Geometry::OrientedPosition &point);

#endif
