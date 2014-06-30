#ifndef ROBOSOCCER_LAYER_ABSTRACTION_STORAGE_H
#define ROBOSOCCER_LAYER_ABSTRACTION_STORAGE_H

#include "layer/abstraction/ball.h"
#include "layer/abstraction/readablerobot.h"
#include "layer/abstraction/controllablerobot.h"
#include "layer/abstraction/refereebase.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class Storage
	{
	public:
		virtual ~Storage() {}

		virtual Ball & getBall() = 0;
		virtual ReadableRobot & getEnemyRobot(unsigned int number)  = 0;
		virtual ControllableRobot& getOwnRobot(unsigned int number) = 0;
		virtual RefereeBase& getReferee() = 0;
	};
}
}
}

#endif


