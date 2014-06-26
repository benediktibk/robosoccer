#include "layer/control/preparepenalty.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/control/userinputfetcher.h"
#include "layer/abstraction/refereebase.h"
#include <assert.h>

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenalty::PreparePenalty(
		Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball,
		Autonomous::TargetPositionFetcher const &targetPositionFetcher,
		FieldPositionCheckerGoalkeeper const &fieldPositionCheckerGoalKeeper,
		UserInputFetcher *userInputFetcher) :
	RoboSoccerState(
		logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher,
		fieldPositionCheckerGoalKeeper, false),
	m_userInputFetcher(userInputFetcher)
{
	assert(userInputFetcher != 0);
}

PreparePenalty::~PreparePenalty()
{
	delete m_userInputFetcher;
	m_userInputFetcher = 0;
}

State *PreparePenalty::nextState()
{
	if (!m_userInputFetcher->selectionMade())
		return 0;

	if (m_userInputFetcher->playOffensive())
		return new PreparePenaltyOffensive(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);
	else
		return new PreparePenaltyDefensive(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);
}

string PreparePenalty::getName()
{
	return string("prepare penalty");
}

void PreparePenalty::updateInternal()
{
	m_userInputFetcher->update();
}
