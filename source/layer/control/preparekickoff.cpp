#include "layer/control/preparekickoff.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOff::PrepareKickOff(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PrepareKickOff::nextState()
{
	return 0;
}

string PrepareKickOff::getName()
{
	return string("prepare kick off");
}

void PrepareKickOff::updateInternal()
{

}

