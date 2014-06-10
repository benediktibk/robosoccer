#ifndef ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERMOCK_H

#include "layer/abstraction/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class FieldPositionCheckerMock :
			public FieldPositionChecker
	{
	public:
		FieldPositionCheckerMock();

		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;

		void setAllCoordinatesOutside(bool value);

	private:
		bool m_allCoordinatesOutside;
	};
}
}
}

#endif


