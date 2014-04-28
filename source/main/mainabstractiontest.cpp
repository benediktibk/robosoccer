#include "layer/abstraction/ballimpl.h"
#include "layer/abstraction/readablerobotimpl.h"
#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/refereebase.h"
#include "layer/control/pause.h"
#include "common/geometry/point.h"
#include "common/geometry/pose.h"
#include "common/logging/loggerimpl.h"
#include "common/states/statemachine.h"
#include "common/other/console.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Common::Other;
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
	cout << "current ball orientation is " << ball.getRotation() << endl;
	cout << "current position of enemy robot is " << enemyRobot.getPose() << endl;

	cout << "moving own robot to position (0, 0) after next keypress" << endl;
	getchar();
	ownRobot.gotoPositionPrecise(Point());

	Pause *initialState = new Pause(logger, referee);
	StateMachine stateMachine(initialState);

	cout << "starting to log state changes" << endl;
	cout << "exit with q" << endl;
	while(Console::getAsynchronousInput() != 'q')
		stateMachine.update();

	cout << "job should be done, closing the application" << endl;
	return 0;
}
