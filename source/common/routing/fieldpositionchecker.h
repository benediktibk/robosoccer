#ifndef ROBOSOCCER_COMMON_ROUTING_FIELDPOSITIONCHECKER_H
#define ROBOSOCCER_COMMON_ROUTING_FIELDPOSITIONCHECKER_H

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
}

namespace Routing
{
class FieldPositionChecker
{
public:
	virtual ~FieldPositionChecker() { }

	virtual bool isPointInsideField(Geometry::Point const &position) const = 0;
};
}
}
}

#endif
