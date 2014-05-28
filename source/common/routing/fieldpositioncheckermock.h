#ifndef ROBOSOCCER_COMMON_ROUTING_FIELDPOSITIONCHECKERMOCK_H
#define ROBOSOCCER_COMMON_ROUTING_FIELDPOSITIONCHECKERMOCK_H

#include "common/routing/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class FieldPositionCheckerMock :
			public FieldPositionChecker
	{
	public:
		FieldPositionCheckerMock();

		virtual bool isPointInsideField(Geometry::Point const &position) const;

		void setNegativeCoordinatesOutside(bool value);
		void setAllCoordinatesOutside(bool value);

	private:
		bool m_negativeCoordinatesOutside;
		bool m_allPointsOutside;
	};
}
}
}

#endif
