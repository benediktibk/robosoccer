#include "layer/control/play.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

Play::Play(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *Play::nextState()
{
	return 0;
}

string Play::getName()
{
	return string("play");
}

void Play::updateInternal()
{

}
