#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTERMOCK_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTERMOCK_H

#include "common/routing/router.h"
#include "common/routing/route.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class RouterMock :
			public Router
	{
	public:
		RouterMock();

		virtual Route calculateRoute(
				const Geometry::OrientedPosition &start, const Geometry::OrientedPosition &end, const FieldPositionChecker &field,
				const Geometry::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool ignoreFinalOrientation,
				const std::vector<Geometry::Circle> &obstacles) const;
		void setChessMode(bool value);

		void setRoute(const Geometry::Point &one, const Geometry::Point &two, const Geometry::Point &three);
		void setInvalidRoute();

	private:
		bool m_chessMode;
		bool m_routeSet;
		Route m_route;
	};
}
}
}

#endif


