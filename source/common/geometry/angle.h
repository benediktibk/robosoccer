#ifndef ROBOSOCCER_COMMON_GEOMETRY_ANGLE_H
#define ROBOSOCCER_COMMON_GEOMETRY_ANGLE_H

#include <ostream>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;

	class Angle
	{
	public:
		Angle();
		Angle(double value);
		Angle(const Point &source, const Point &targetOne, const Point &targetTwo);
		Angle(const Point &start, const Point &end);

		double getValueBetweenMinusPiAndPi() const;
		double getValueBetweenZeroAndTwoPi() const;
		void abs();
		bool isObtuse() const;

		Angle operator+(const Angle &rhs) const;
		Angle operator-(const Angle &rhs) const;
		Angle operator*(double value) const;
		Angle operator/(double value) const;
		bool operator==(const Angle &rhs) const;

	public:
		static Angle getHalfRotation();
		static Angle getQuarterRotation();
		static Angle getFullRotation();
		static Angle getEighthRotation();
		static Angle getThreeQuarterRotation();
		static Angle convertFromDegreeToRadiant(double angle);

	private:
		void fixRange();

	private:
		double m_value;
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Common::Geometry::Angle &angle);

#endif
