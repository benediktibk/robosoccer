#include "layer/control/penaltydefensive.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

PenaltyDefensive::PenaltyDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PenaltyDefensive::nextState()
{
	return 0;
}

string PenaltyDefensive::getName()
{
	return string("penalty defensive");
}

void PenaltyDefensive::updateInternal()
{

}