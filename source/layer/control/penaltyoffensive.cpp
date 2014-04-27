#include "layer/control/penaltyoffensive.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

PenaltyOffensive::PenaltyOffensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PenaltyOffensive::nextState()
{
	return 0;
}

string PenaltyOffensive::getName()
{
	return string("penalty offensive");
}

void PenaltyOffensive::updateInternal()
{

}