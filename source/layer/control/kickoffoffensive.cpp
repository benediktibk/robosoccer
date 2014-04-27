#include "layer/control/kickoffoffensive.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

KickOffOffensive::KickOffOffensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *KickOffOffensive::nextState()
{
	return 0;
}

string KickOffOffensive::getName()
{
	return string("kick off offensive");
}

void KickOffOffensive::updateInternal()
{

}