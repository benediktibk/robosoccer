#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/abstraction/fieldpositioncheckerfieldplayer.h"
#include "layer/autonomous/robot.h"
#include "common/logging/loggerimpl.h"
#include "common/time/watchimpl.h"
#include "common/geometry/pose.h"
#include "layer/control/treenodedeciderisonerobotinshootingrange.h"
#include "layer/control/treenoderesult.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Layer::Control;

int main(int, char**)
{
	cout << "creating objects" << endl;
	LoggerImpl logger;
	WatchImpl watch;
	StorageImpl storage(14, TeamColorRed, logger, watch);
	FieldPositionCheckerGoalkeeper fieldPositionCheckerGoalKeeper;
	FieldPositionCheckerFieldPlayer fieldPositionCheckerFieldPlayer;
	ObstacleFetcherImpl obstacleFetcher;
	TeamImpl team(storage, watch, logger, fieldPositionCheckerGoalKeeper, fieldPositionCheckerFieldPlayer, obstacleFetcher);
	EnemyTeamImpl enemyTeam(storage);
	IntelligentBallImpl ball(storage.getBall());
	TargetPositionFetcher targetPositionFetcher;
	RefereeMock referee;
	targetPositionFetcher.setFieldSide(referee.getOwnFieldSide());

	while (true)
	{
		team.getFirstFieldPlayer().update();
		team.getSecondFieldPlayer().update();
		team.getGoalie().update();

		TreeNode *node = new TreeNodeDeciderIsOneRobotInShootingRange(logger, referee, team, enemyTeam, ball, targetPositionFetcher, TreeNode::FollowBallRobotNone);
		while (node->decide())
		{
			TreeNodeDecider *current = dynamic_cast<TreeNodeDecider*>(node);
			node = current->getChild();
			delete current;
		}

		TreeNodeResult *result = dynamic_cast<TreeNodeResult*>(node);
		result->execute();
		delete result;

		usleep(10000);
	}
}
