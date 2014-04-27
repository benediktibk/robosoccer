#include "layer/control/preparekickoffdefensive.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOffDefensive::PrepareKickOffDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PrepareKickOffDefensive::nextState()
{
	return 0;
}

string PrepareKickOffDefensive::getName()
{
	return string("prepare kick off defensive");
}

void PrepareKickOffDefensive::updateInternal()
{

}