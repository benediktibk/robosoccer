#include "layer/control/preparepenalty.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenalty::PreparePenalty(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PreparePenalty::nextState()
{
	return 0;
}

string PreparePenalty::getName()
{
	return string("prepare penalty");
}

void PreparePenalty::updateInternal()
{

}
