#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTE_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTE_H

#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include <list>
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Pose;
}
namespace Routing
{
	class Route
	{
	public:
		Route();
		Route(double width);

		void addPoint(const Geometry::Point &point);
		void add(const Route &route);
		size_t getPointCount() const;
		bool isValid() const;
		const Geometry::Point& getLastPoint() const;
		const Geometry::Point& getNextToLastPoint() const;
		const Geometry::Point& getSecondPoint() const;
		const Geometry::Point& getFirstPoint() const;
		const Geometry::Point& getThirdPoint() const;
		std::list<Geometry::Point> getAllPoints() const;
		void removeFirstPoint();
		double getWidth() const;
		bool intersectsWith(const std::vector<Geometry::Circle> &objects) const;
		void replaceFirstPoint(const Geometry::Point &point);
		double getLength() const;
		double getLengthOfLastSegment() const;
		void splitLastSegment(double lengthOfLastSegment);


	private:
		std::list<Geometry::Point> m_points;
		double m_width;
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Common::Routing::Route &route);

#endif
