#include "layer/control/preparepenaltyoffensive.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenaltyOffensive::PreparePenaltyOffensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PreparePenaltyOffensive::nextState()
{
	return 0;
}

string PreparePenaltyOffensive::getName()
{
	return string("prepare penalty offensive");
}

void PreparePenaltyOffensive::updateInternal()
{

}
