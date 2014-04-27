#include "layer/control/preparepenaltydefensive.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenaltyDefensive::PreparePenaltyDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PreparePenaltyDefensive::nextState()
{
	return 0;
}

string PreparePenaltyDefensive::getName()
{
	return string("prepare penalty defensive");
}

void PreparePenaltyDefensive::updateInternal()
{

}