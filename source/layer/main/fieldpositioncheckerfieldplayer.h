#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERFIELDPLAYER_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERFIELDPLAYER_H

#include "common/routing/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class FieldPositionCheckerFieldPlayer
	{
	public:
		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;
	};
}
}
}

#endif


