#include "layer/abstraction/ballimpl.h"
#include "layer/abstraction/readablerobotimpl.h"
#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/refereebase.h"
#include "common/geometry/point.h"
#include "common/geometry/pose.h"
#include "common/logging/loggerimpl.h"
#include "common/other/console.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Other;
using namespace std;

int main(int, char**)
{
	cout << "creating objects from database" << endl;
	LoggerImpl logger;
	StorageImpl storage(14, TeamColorBlue, logger);
	Ball const& ball = storage.getBall();
	ReadableRobot const& enemyRobot = storage.getEnemyRobot(0);
	ControllableRobot &ownRobot = storage.getOwnRobot(0);
	RefereeBase &referee = storage.getReferee();

	cout << "current ball position is " << ball.getPosition() << endl;
	cout << "current ball orientation is " << ball.getRotation() << endl;
	cout << "current pose of enemy robot is " << enemyRobot.getPose() << endl;
	cout << "current pose of own robot is " << ownRobot.getPose() << endl;
	referee.logInformation();
	ownRobot.turn(Angle(0));

	while(true)
	{
		if (referee.playModeChangedSinceLastCall())
			cout << "paused: " << referee.isGamePaused() << ",\tprepare penalty: " << referee.getPrepareForPenalty() << ",\texecute penalty: " << referee.getExecutePenalty() << endl;
	}

	return 0;
}
