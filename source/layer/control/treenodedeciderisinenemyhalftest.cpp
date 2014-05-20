#include "layer/control/treenodedeciderisinenemyhalftest.h"
#include "layer/control/treenodedeciderisinenemyhalf.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"

using namespace RoboSoccer::Layer::Control;

TreeNodeDecider *TreeNodeDeciderIsInEnemyHalfTest::createTestObject()
{
	return new TreeNodeDeciderIsInEnemyHalf(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void TreeNodeDeciderIsInEnemyHalfTest::getChild_ballInOwnZone_defend()
{

}

void TreeNodeDeciderIsInEnemyHalfTest::getChild_ballInEnemyZone_attack()
{

}
