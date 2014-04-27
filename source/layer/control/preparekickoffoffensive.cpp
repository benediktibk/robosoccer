#include "layer/control/preparekickoffoffensive.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOffOffensive::PrepareKickOffOffensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PrepareKickOffOffensive::nextState()
{
	return 0;
}

string PrepareKickOffOffensive::getName()
{
	return string("prepare kick off offensive");
}

void PrepareKickOffOffensive::updateInternal()
{

}

