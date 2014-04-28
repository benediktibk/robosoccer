#include "layer/control/robosoccerstate.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;

RoboSoccerState::RoboSoccerState(Logger &logger, RefereeBase &referee, bool callUpdateOnlyOnce) :
	Common::States::State(logger, callUpdateOnlyOnce),
	m_referee(referee)
{ }