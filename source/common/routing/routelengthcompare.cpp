#include "common/routing/routelengthcompare.h"
#include "common/routing/route.h"

using namespace RoboSoccer::Common::Routing;

RouteLengthCompare::RouteLengthCompare()
{ }

bool RouteLengthCompare::operator()(const Route &one, const Route &two) const
{
	return one.getLength() < two.getLength();
}

