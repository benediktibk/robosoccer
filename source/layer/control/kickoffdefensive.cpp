#include "layer/control/kickoffdefensive.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

KickOffDefensive::KickOffDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *KickOffDefensive::nextState()
{
	return 0;
}

string KickOffDefensive::getName()
{
	return string("kick off defensive");
}

void KickOffDefensive::updateInternal()
{

}