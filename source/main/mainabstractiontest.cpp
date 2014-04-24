#include "layer/abstraction/ballimpl.h"
#include "layer/abstraction/readablerobotimpl.h"
#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/refereebase.h"
#include "common/geometry/point.h"
#include "common/geometry/orientedposition.h"
#include "common/logging/loggerimpl.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

int main(int, char**)
{
	cout << "creating objects from database" << endl;
	LoggerImpl logger;
	StorageImpl storage(14, TeamColorRed, logger);
	Ball const& ball = storage.getBall();
	ReadableRobot const& enemyRobot = storage.getEnemyRobot(0);
	ControllableRobot &ownRobot = storage.getOwnRobot(0);
	RefereeBase &referee = storage.getReferee();

	cout << "current ball position is " << ball.getPosition() << endl;
	cout << "current position of enemy robot is " << enemyRobot.getPosition() << endl;
	cout << "moving own robot to position (0, 0) after next keypress" << endl;

	referee.logInformation();

	getchar();
	ownRobot.gotoPositionPrecise(Point());

	cout << "waiting a little bit" << endl;
	sleep(5);

	cout << "job should be done, closing the application" << endl;
	return 0;
}
