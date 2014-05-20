#include "layer/control/treenodedeciderisinenemyhalftest.h"
#include "layer/control/treenodedeciderisinenemyhalf.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/control/treenoderesultdefendgoal.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNodeDecider *TreeNodeDeciderIsInEnemyHalfTest::createTestNode()
{
	return new TreeNodeDeciderIsInEnemyHalf(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void TreeNodeDeciderIsInEnemyHalfTest::getChild_ballInOwnZone_defend()
{
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);
	m_ball->setPosition(Point(-1.1, 0.3));

	TreeNode *node = m_node->getChild();
	TreeNodeResultDefendGoal *defendGoal = dynamic_cast<TreeNodeResultDefendGoal*>(node);
	CPPUNIT_ASSERT(defendGoal != 0);
}

void TreeNodeDeciderIsInEnemyHalfTest::getChild_ballInEnemyZone_attack()
{
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);
	m_ball->setPosition(Point(1.1, 0.3));

	TreeNode *node = m_node->getChild();
	TreeNodeResultDefendGoal *defendGoal = dynamic_cast<TreeNodeResultDefendGoal*>(node);
	CPPUNIT_ASSERT(defendGoal == 0);
}
