#ifndef ROBOSOCCER_COMMON_GEOMETRY_POSE_H
#define ROBOSOCCER_COMMON_GEOMETRY_POSE_H

#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include <ostream>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Pose
	{
	public:
		Pose();
		Pose(const Point &point, const Angle &orientation);

		void setOrientation(const Angle &orientation);
		const Angle& getOrientation() const;
		void setPosition(const Point &position);
		const Point& getPosition() const;
		double distanceTo(const Pose &point) const;
		void read(const std::string &data);
		Angle getRelativeOrientationTo(const Point &point) const;

		bool operator ==(const Pose &position) const;
		Pose operator*(double value) const;
		Pose operator/(double value) const;
		Pose operator+(const Pose &point) const;
		Pose operator-(const Pose &point) const;
		void operator*=(double value);
		operator Point() const;

	private:
		Point m_position;
		Angle m_orientation;
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Common::Geometry::Pose &point);

#endif
